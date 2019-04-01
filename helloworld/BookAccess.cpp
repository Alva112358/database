#include "BookAccess.h"
#include <sstream>
#include <ctime>
BookAccess::BookAccess() {
	mysql_init(&mysql);
	if (mysql_real_connect(&mysql, "localhost", "root", "dsalfjsljf", "bookshop", 3306, 0, 0)) {
		cout << "Successfully connect to the database!" << endl;
	}
	else {
		cout << "Fail to connect to the database!" << endl;
	}
};

BookAccess::~BookAccess() {
	mysql_close(&mysql);
}


/*------------------------------------------------进货---------------------------------------------------------*/
//返回书的供应商和单价数组
vector<supplierAndMoney> BookAccess::getTotalNumberByBookName(string bookName) {
	vector<supplierAndMoney> Info;
	string queryString = "SELECT supplier.sid,supplier.sprice FROM supplier WHERE supplier.sname = \"" + bookName + "\"";
	if (mysql_query(&mysql, queryString.c_str())) {
		cout << mysql_error(&mysql) << endl;
	}
	else {
		cout << "Successfully query!" << endl;
		MYSQL_RES * result = mysql_store_result(&mysql);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(result)) {
			string supplierName = row[0];
            string supplierPrice = row[1];
            supplierAndMoney temp = supplierAndMoney(supplierName, supplierPrice);
			Info.push_back(temp);
		}
		mysql_free_result(result);
	}
	return Info;
}

//返回新华书店中该书的库存量(finish)
int BookAccess::getTotalBookNumber(string bookName) {
	stringstream ss;
	int totalNumber = 0;
	string queryString = "SELECT bookshop.bnumber FROM bookshop WHERE bookshop.bname = \"" + bookName + "\"";
	if (mysql_query(&mysql, queryString.c_str())) {
		cout << mysql_error(&mysql) << endl;
	}
	else {
        cout << "Query Successfully!" << endl;
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW  row = mysql_fetch_row(result);
        if (row != NULL) {
            ss << row[0];
            ss >> totalNumber;
            mysql_free_result(result);
        }
        // 无该书籍库存
        else {
            cout << "This book is not existed!" << endl;
            totalNumber = -1;
        }

	}
	return totalNumber;
}

//返回销售库中该书的销售量(finish)
int BookAccess::getSellBookNumber(string bookName) {

	int totalNumber = 0;
	string queryString = "SELECT selltable.ssnumber, selltable.ssIsReturn FROM selltable WHERE selltable.ssIsReturn = \"0\" and selltable.ssname = \"" + bookName + "\"";
	if (mysql_query(&mysql, queryString.c_str())) {
		cout << mysql_error(&mysql) << endl;
	}
	else {
		cout << "Query Successfully!" << endl;
		MYSQL_RES * result = mysql_store_result(&mysql);
		MYSQL_ROW row;

		while ((row = (mysql_fetch_row(result)))) {
			int temp = 0;
			stringstream ss;
			ss << row[0];
			ss >> temp;
			totalNumber += temp;
		}
		mysql_free_result(result);
	}
	return totalNumber;
}

//根据供应商和进货量进货，并修改库存量，同时生成进货表
purchaseInfo BookAccess::purchaseBook(string supplier, string bookName, string purchaseNumber) {
    purchaseInfo Info;
     // 检查是否存在此供应商和书籍
    string queryString = "SELECT COUNT(*) FROM supplier WHERE supplier.sid = \"" + supplier + "\" and supplier.sname = \"" + bookName + "\";";
    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int isExist = atoi(row[0]);
        if (isExist == 0) {
            Info.purchaseId = "-1";
            return Info;
        }
    }


    int bookNumber;
    stringstream ss;
    ss << purchaseNumber;
    ss >> bookNumber;
    queryString = "UPDATE bookshop SET bnumber = bnumber + " + purchaseNumber;

    // 更新库存量
    queryString += " WHERE bookshop.bname = \"" + bookName + "\"";

    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        // 根据supplier获取图书单价
        queryString = "SELECT supplier.sprice FROM supplier WHERE supplier.sid = \"" + supplier;
        queryString += "\" and supplier.sname = \"";
        queryString += bookName;
        queryString += "\"";
        if (mysql_query(&mysql, queryString.c_str())) {
            cout << mysql_error(&mysql) << endl;
        }
        else {
            MYSQL_RES * result = mysql_store_result(&mysql);
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                string price = row[0];
                // 插入purchase表
                string currentDate = getCurrentDate();
                queryString = "INSERT INTO purchase VALUES (null, \"" + bookName;
                queryString += "\", \"";
                queryString += currentDate;
                queryString += "\", ";
                queryString += purchaseNumber;
                queryString += ", ";
                queryString += price;
                queryString += ");";

                mysql_query(&mysql, queryString.c_str());

                // 查询bookshop中是否有这本书
                queryString = "SELECT COUNT(*) FROM bookshop WHERE bookshop.bname = \"" + bookName + "\";";
                if (mysql_query(&mysql, queryString.c_str())) {
                    cout << mysql_error(&mysql) << endl;
                }
                else {
                    // 获取该书在书店中的数目
                    MYSQL_RES * result = mysql_store_result(&mysql);
                    MYSQL_ROW  row = mysql_fetch_row(result);
                    int number = atoi(row[0]);
                    if (number == 0) {
                        // 插入到书店中
                        queryString = "INSERT INTO bookshop VALUES (\"" + bookName + "\"," + purchaseNumber + "," + price + ")";
                        if (mysql_query(&mysql, queryString.c_str())) {
                            cout << mysql_error(&mysql) << endl;
                        }
                    }
                }

                // 统计进货表记录数量，用于显示id
                queryString = "SELECT COUNT(*) FROM purchase";

                if (mysql_query(&mysql, queryString.c_str())) {
                    cout << mysql_error(&mysql) << endl;
                }
                else {
                    // 生成进货表
                    MYSQL_RES * result = mysql_store_result(&mysql);
                    MYSQL_ROW  row = mysql_fetch_row(result);

                    Info.bookName = bookName;
                    Info.purchaseData = currentDate;
                    Info.purchaseId = row[0];
                    Info.purchaseNumber = bookNumber;
                    double money = atof(price.c_str());
                    money = money * bookNumber;
                    stringstream ss;
                    ss << money;
                    string temp;
                    ss >> temp;
                    Info.totalMoney = temp;
                }
            }
            else {
                cout << "No such supplier" << endl;
            }
        }
    }
    return Info;
}
/*------------------------------------------------进货---------------------------------------------------------*/







/*------------------------------------------------销售---------------------------------------------------------*/
//返回新华书店中该书的库存量
//int getTotalBookNumber(char[20] bookName);

//如果getTotalBookNumber()>0，则可以销售，修改库存量和销售库，并返回销售表单(finish，差日期，返回id)
sellInfo BookAccess::sellBook(string bookName, string sellNumber) {
    sellInfo Info;
    // string bookNumber = std::to_string(sellNumber);
    //检查是否存在该书籍
    string queryString = "SELECT COUNT(*) FROM bookshop WHERE bookshop.bname = \"" + bookName + "\"";
    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW  row = mysql_fetch_row(result);
        int isExistBook = atoi(row[0]);
        if (isExistBook == 0) {
            cout << "The book is not existed in the bookshop." << endl;
            Info.sellId = "-2";
            return Info;
        }
    }

    int bookLeftNumber = getTotalBookNumber(bookName);
    cout << "Number: " << bookLeftNumber << endl;
    if (bookLeftNumber < atoi(sellNumber.c_str())) {
        cout << "The number of the book is not enough." << endl;
        Info.sellId = "-1";
        return Info;
    }

    int bookNumber;
    stringstream ss;
    ss << sellNumber;
    ss >> bookNumber;

    // 更新库存量
    queryString = "UPDATE bookshop SET bnumber = bnumber - " + sellNumber;
    queryString += " WHERE bookshop.bname = \"" + bookName + "\"";

    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        // 获取书本单价
        queryString = "SELECT bookshop.bprice FROM bookshop WHERE bookshop.bname = \"" + bookName + "\"";
        mysql_query(&mysql, queryString.c_str());
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW  row = mysql_fetch_row(result);
        string price = row[0];

        // 插入销售表
        queryString = "INSERT INTO selltable VALUES (null, \"" + bookName;
        queryString += "\", \"2018-07-04\", \"";
        queryString += price;
        queryString += "\", \"";
        queryString += sellNumber;
        queryString += "\", \"0\");";

        mysql_query(&mysql, queryString.c_str());

        // 统计退货表记录数量，用于显示id
        queryString = "SELECT COUNT(*) FROM selltable";

        if (mysql_query(&mysql, queryString.c_str())) {
            cout << mysql_error(&mysql) << endl;
        }
        else {
            MYSQL_RES * result = mysql_store_result(&mysql);
            MYSQL_ROW  row = mysql_fetch_row(result);

            // 生成销售表单
            Info.sellDate = "2018-07-04";
            Info.sellId = row[0];
            Info.sellName = bookName;
            Info.sellNumber = sellNumber;
            Info.sellPrice = price;

            /*test*/
            cout << Info.sellPrice << endl;
        }
    }
    return Info;
}
/*------------------------------------------------销售----------------------------------------------------------*/







/*------------------------------------------------退书---------------------------------------------------------*/
//顾客退书，自动修改库存量，把本次退货的信息添加到退货库.(finish,差日期，返回id)
// ReturnId: 不存在购货记录(-1)，退的数量比买的数量多(-2)，第二次退款(-3)
returnInfo BookAccess::returnBook(string bookName, string bookSellId, string bookSellNumber) {
    returnInfo Info;
    // 检测该书是否有购买记录
    string queryString = "SELECT COUNT(*) FROM selltable WHERE selltable.ssname = \"" + bookName + "\" and selltable.ssid = " + bookSellId;
    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW  row = mysql_fetch_row(result);
        int isExist = atoi(row[0]);
        if (isExist == 0) {
            Info.returnId = "-1";
            return Info;
        }
    }

    // 查询是否存在对应的销售记录
    queryString = "SELECT selltable.ssnumber FROM selltable WHERE selltable.ssIsReturn = 0 and selltable.ssid = " + bookSellId;
    if (mysql_query(&mysql, queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW  row = mysql_fetch_row(result);
        // 存在销售记录且首次退货
        if (row != NULL) {
            int buyNumber = atoi(row[0]); // 第一次购买的数量
            // 退货数量不可以比购买数量多
            int sellNumber = atoi(bookSellNumber.c_str());
            if (sellNumber > buyNumber) {
                cout << "Warning!" << endl;
                Info.returnId = "-2";
                return Info;
            }

            // 更新库存
            queryString = "UPDATE bookshop SET bnumber = bnumber + " + bookSellNumber;
            queryString += " WHERE bookshop.bname = \"" + bookName + "\"";

            if (mysql_query(&mysql, queryString.c_str())) {
                cout << mysql_error(&mysql) << endl;
            }
            else {
                // 更新selltable
                queryString = "UPDATE selltable SET ssnumber = ssnumber - " + bookSellNumber;
                queryString += " WHERE selltable.ssid = \"" + bookSellId + "\"";
                mysql_query(&mysql, queryString.c_str());

                queryString = "UPDATE selltable SET ssIsReturn = 1";
                queryString += " WHERE selltable.ssid = \"" + bookSellId + "\"";
                if (mysql_query(&mysql, queryString.c_str())) {
                    cout << mysql_error(&mysql) << endl;
                }
                else {
                    // 添加退货记录
                    string currentDate = getCurrentDate();
                    queryString = "INSERT INTO returntable VALUES (null, \"" + bookName;
                    queryString += "\", \"";
                    queryString += currentDate;
                    queryString += "\", \"";
                    queryString += bookSellNumber;
                    queryString += "\");";
                    mysql_query(&mysql, queryString.c_str());

                    // 统计退货表记录数量，用于显示id
                    queryString = "SELECT COUNT(*) FROM returntable";

                    if (mysql_query(&mysql, queryString.c_str())) {
                        cout << mysql_error(&mysql) << endl;
                    }
                    else {
                        MYSQL_RES * result = mysql_store_result(&mysql);
                        MYSQL_ROW  row = mysql_fetch_row(result);
                        // 生成退货表单
                        Info.returnId = row[0];
                        Info.returnName = bookName;
                        Info.returnNumber = bookSellNumber;
                        Info.returnData = currentDate;
                    }
                }
            }
        }
        // 不存在销售记录或不允许第二次退货
        else {
            cout << "Can't return twice!" << endl;
            Info.returnId = "-3";
        }
    }
    return Info;
}
/*------------------------------------------------退书---------------------------------------------------------*/








/*------------------------------------------------统计---------------------------------------------------------*/
//输出销售报表，内容为每月销售总额，销售总量及排行榜.
//返回的orderList应该是根据销售总量进行排行后的结果.
vector<orderList> BookAccess::printTotalAndOrder(string today) {
    vector<orderList> List;
    string previousMonth,futureMonth;
    for (int i = 0; i <= 5; i++) {
        previousMonth += today[i];
        futureMonth += today[i];
    }
    previousMonth += today[6];
    futureMonth += today[6] + 1;
    previousMonth += "-01";
    futureMonth += "-01";
    string queryString = "SELECT selltable.ssname,sum(selltable.ssprice * selltable.ssnumber) AS totalmoney,sum(selltable.ssnumber) AS totalSell FROM selltable WHERE selltable.ssdate >= \"" + previousMonth;
    queryString += "\" and selltable.ssdate < \"" + futureMonth;
    queryString += "\" GROUP BY selltable.ssname ORDER BY totalSell";
    if (mysql_query(&mysql,queryString.c_str())) {
        cout << mysql_error(&mysql) << endl;
    }
    else {
        cout << "Successfully query" << endl;
        MYSQL_RES * result = mysql_store_result(&mysql);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(result)) {
            string _bookname = row[0];
            string _totalMoneyLastMonth = row[1];
            string _sellNumberLastMonth = row[2];
            orderList temp = orderList(_bookname, _sellNumberLastMonth, _totalMoneyLastMonth);
            cout << _bookname << " " << _totalMoneyLastMonth << " " << _sellNumberLastMonth << endl;
            List.push_back(temp);
        }
        mysql_free_result(result);
    }
    return List;
}
/*------------------------------------------------统计---------------------------------------------------------*/


string BookAccess::getCurrentDate() {
    time_t rawtime;
    struct tm ptminfo;
    time(&rawtime);
    localtime_s(&ptminfo, &rawtime);

    int year = ptminfo.tm_year + 1900;
    int month = ptminfo.tm_mon + 1;
    int day = ptminfo.tm_mday;
    string _year, _month, _day;
    string today;

    stringstream ss;
    ss << year;
    ss >> _year;
    ss.clear();
    ss << month;
    ss >> _month;
    ss.clear();
    ss << day;
    ss >> _day;
    if (_month.length() == 1) _month = "0" + _month;
    if (_day.length() == 1) _day = "0" + _day;
    today = today + _year + "-" + _month + "-" + _day;
    cout << today << endl;
    return today;
}

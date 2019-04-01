#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <winsock.h>
#include <C:/mysql-5.7.20-winx64/include/mysql.h>

using namespace std;

struct supplierAndMoney {
	string supplier;
    string money;
	supplierAndMoney() {
	}
    supplierAndMoney(string _supplier, string _money) {
		//strcpy_s(supplier, 20, _supplier);
		supplier = _supplier;
		money = _money;
	}
};

struct purchaseInfo {
    string purchaseNumber;
	string purchaseData;
    string purchaseId;
	string bookName;
    string totalMoney;
	purchaseInfo() {
        // totalMoney = 0;
	}
    purchaseInfo(string _purchaseNumber, string _purchaseData, string _purchaseId, string _bookName, string _totalMoney) {
		purchaseNumber = _purchaseNumber;
		purchaseData = _purchaseData;
		purchaseId = _purchaseId;
		bookName = _bookName;
		totalMoney = _totalMoney;
	}
};

struct returnInfo {
    string returnNumber;
	string returnData;
	string returnName;
    string returnId;
	returnInfo() {
        // returnNumber = -1;
	}
    returnInfo(string _returnNumber, string _returnData, string _returnName, string _returnId) {
		returnNumber = _returnNumber;
		returnData = _returnData;
		//strcpy_s(returnName,strlen(_returnName)+1,_returnName);
		returnName = _returnName;
		returnId = _returnId;
	}
};

struct sellInfo {
    string sellId;
    string sellNumber;
	string sellDate;
	string sellName;
    string sellPrice;
	sellInfo() {
        // sellNumber = -1;
	}
    sellInfo(string _sellId, string _sellNumber, string _sellDate, string _sellName, string _sellPrice) {
		sellId = _sellId;
		sellNumber = _sellNumber;
		//strcpy_s(sellData,strlen(_sellData)+1,_sellData);
		sellDate = _sellDate;
		//strcpy_s(sellName,strlen(_sellName)+1,_sellName);
		sellName = _sellName;
		sellPrice = _sellPrice;
	}
};

struct orderList {
    string bookName;
    string sellNumberLastMonth;
    string totalMoneyLastMonth;
    orderList() {
    }
    orderList(string _bookName, string _sellNumberLastMonth, string _totalMoneyLastMonth) {
        bookName = _bookName;
        //strcpy_s(bookName,strlen(_bookName)+1,_bookName);
        sellNumberLastMonth = _sellNumberLastMonth;
        totalMoneyLastMonth = _totalMoneyLastMonth;
    }
};

class BookAccess {
public:
	BookAccess();
	~BookAccess();
	/*------------------------------------------------进货---------------------------------------------------------*/
	/*根据供应商报价选择供应商.输出一份进货单并自动修改库存量，把本次进货信息添加到进货库--------*/
	//返回书的供应商和单价数组
	vector<supplierAndMoney> getTotalNumberByBookName(string bookName);
	//返回新华书店中该书的库存量
	int getTotalBookNumber(string bookName);
	//返回销售库中该书的销售量
	int getSellBookNumber(string bookName);
	//根据供应商和进货量进货，并修改库存量，同时生成进货表
    purchaseInfo purchaseBook(string supplier, string bookName, string purchaseNumber);
	/*------------------------------------------------进货---------------------------------------------------------*/



	/*------------------------------------------------销售---------------------------------------------------------*/
	/*销售书籍，输入顾客要买书籍信息，自动显示此书库存量，如果可以销售,打印销售单并修改库存，同时把此次销售的相关信息添加到日销售库 */
	//返回新华书店中该书的库存量
	//int getTotalBookNumber(string[20] bookName);

	//如果getTotalBookNumber()>0，则可以销售，修改库存量和销售库，并返回销售表单
    sellInfo sellBook(string bookName, string sellNumber);
	/*------------------------------------------------销售----------------------------------------------------------*/



	/*------------------------------------------------退书---------------------------------------------------------*/
	//顾客退书，自动修改库存量，把本次退货的信息添加到退货库.
    returnInfo returnBook(string bookName, string bookSellId, string bookSellNumber);
	/*------------------------------------------------退书---------------------------------------------------------*/



	/*------------------------------------------------统计---------------------------------------------------------*/
	//输出销售报表，内容为每月销售总额，销售总量及排行榜.
	//返回的orderList应该是根据销售总量进行排行后的结果.
    vector<orderList> printTotalAndOrder(string today);
	/*------------------------------------------------统计---------------------------------------------------------*/
private:
    string getCurrentDate();
	MYSQL mysql;
};


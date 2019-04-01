#include "ui_purchaseDialog.h"
#include "purchasedialog.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    searchbutton = new QPushButton(this);
    searchbutton->setGeometry(QRect(510,260,100,55));
    searchbutton->setText("Search");

    submitbutton = new QPushButton(this);
    submitbutton->setGeometry(QRect(730, 345, 100, 55));
    submitbutton->setText("Submit");

    connect(submitbutton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(searchbutton, SIGNAL(clicked()), this, SLOT(getBookStock()));
}
/*
    根据书名查询库存量和销售量
*/
void MyDialog::getBookStock() {
    QString qbookName = ui->book->toPlainText();
    if (qbookName == "") {
        return;
    }
    string bookName = string((const char*)qbookName.toLocal8Bit());
    //cout << temp << endl;
    vector<supplierAndMoney> data = bookAccess.getTotalNumberByBookName(bookName);
    QString qsupplier;
    QString qmoney;
    QString text;
    for (int i = 0; i < data.size(); i++) {
        text += "Supplier: ";
        qsupplier = QString(QString::fromLocal8Bit(data[i].supplier.c_str()));
        qmoney = QString(QString::fromLocal8Bit(data[i].money.c_str()));
        text += qsupplier;
        text += "   Price: $ ";
        text += qmoney;
        text += "\n";
    }

    int stockNumber = bookAccess.getTotalBookNumber(bookName);
    string number;
    stringstream ss;
    ss << stockNumber;
    ss >> number;
    // QString text;
    text += "\n\nStock: ";
    if (stockNumber != -1) {

        text += QString(QString::fromLocal8Bit(number.c_str()));
        ui->textBrowser->setText(text);
    }
    else {
        //text = "The book is not in our stock!";
        //text += "\nCannot purchase from supplier!";
        text += "0";
        ui->textBrowser->setText(text);
    }

    ui->textBrowser->setText(text);
}

/*
    根据供应商id和进货量提交订单
*/
void MyDialog::submit(){
    QString qid = ui->ID->toPlainText();
    QString qbookName = ui->book->toPlainText();
    QString qbookNumber = ui->BookNumber->toPlainText();

    if (qid == "" || qbookName == "" || qbookNumber == "") {
        // Clear Message
        ui->textBrowser->setText("");
        return;
    }

    string id = string((const char*)qid.toLocal8Bit());
    string bookName = string((const char*)qbookName.toLocal8Bit());
    string bookNumber = string((const char*)qbookNumber.toLocal8Bit());

    if (!checkIfNumbers(bookNumber)) {
        ui->textBrowser->setText("Please input number in BookNumber");
        return;
    }

    purchaseInfo data = bookAccess.purchaseBook(id, bookName, bookNumber);

    QString returnDate = QString(QString::fromLocal8Bit(data.purchaseData.c_str()));
    QString returnID = QString(QString::fromLocal8Bit(data.purchaseId.c_str()));
    QString returnBookName = QString(QString::fromLocal8Bit(data.bookName.c_str()));
    QString returnTotalMoney = QString(QString::fromLocal8Bit(data.totalMoney.c_str()));
    if (returnID == "-1") {
        QString text = "Supplier is not existed!";
        ui->textBrowser->setText(text);
    }
    else {
        QString text = "ID: " + returnID
                        + "\nBookName: " + returnBookName
                        + "\nGross: " + returnTotalMoney
                        + "\nDate: " + returnDate;
        ui->textBrowser->setText(text);
    }
}

MyDialog::~MyDialog()
{
    delete ui;
}

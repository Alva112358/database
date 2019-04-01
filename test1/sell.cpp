#include "sell.h"
#include "ui_sell.h"
#include <string>
#include <iostream>
#include <sstream>
Sell::Sell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sell)
{
    ui->setupUi(this);
    connect(ui->searchbutton, SIGNAL(clicked()), this, SLOT(getBookStock()));
    connect(ui->submitbutton, SIGNAL(clicked()), this, SLOT(sell()));
}

/*
    输入书名，显示库存量
*/
void Sell::getBookStock() {
    // Clear messages
    ui->textBrowser->setText("");
    ui->textBrowser_2->setText("");

    QString qbookName = ui->BookName->toPlainText();
    if (qbookName == "") {
        return;
    }
    string bookName = string((const char*)qbookName.toLocal8Bit());

    int stockNumber = bookAccess.getTotalBookNumber(bookName);
    string number;
    stringstream ss;
    ss << stockNumber;
    ss >> number;
    cout << number;
    QString text;
    if (stockNumber != -1) {
        text = QString(QString::fromLocal8Bit(number.c_str()));
        ui->textBrowser_2->setText(text);
    }
    else {
        text = "The book is not in our stock!";
        ui->textBrowser->setText(text);
    }
}

/*
    输入销售量，根据书名销售
*/
void Sell::sell() {
    // Clear Message
    ui->textBrowser->setText("");

    QString qbookName = ui->BookName->toPlainText();
    QString qbookNumber = ui->BookNumber->toPlainText();
    if (qbookName == "" || qbookNumber == "") {
        // Clear Message
        ui->textBrowser->setText("");
        ui->textBrowser_2->setText("");
        return;
    }
    string bookName = string((const char*)qbookName.toLocal8Bit());
    string bookNumber = string((const char*)qbookNumber.toLocal8Bit());

    if (!checkIfNumbers(bookNumber)) {
        ui->textBrowser->setText("Please input number in [Number]");
        return;
    }

    sellInfo data = bookAccess.sellBook(bookName, bookNumber);
    string returnID = data.sellId;
    string returnNumber = data.sellNumber;
    string returnDate = data.sellDate;
    string returnName = data.sellName;
    string returnPrice = data.sellPrice;
    QString ID = QString(QString::fromLocal8Bit(returnID.c_str()));
    QString number = QString(QString::fromLocal8Bit(returnNumber.c_str()));
    QString date = QString(QString::fromLocal8Bit(returnDate.c_str()));
    QString name = QString(QString::fromLocal8Bit(returnName.c_str()));
    QString price = QString(QString::fromLocal8Bit(returnPrice.c_str()));

    if (returnID == "-1") {
        QString text = "Not enough book!";
        ui->textBrowser->setText(text);
    }
    else if (returnID == "-2") {
        QString text = "This book is not in our stock!";
        ui->textBrowser->setText(text);
    }
    else {
        QString text = "ID: " + ID
                        + "\nName: " + name
                        + "\nNumber: " + number
                        + "\nPrice: " + price
                        + "\nDate: " + date;
        ui->textBrowser->setText(text);
    }

}
Sell::~Sell()
{
    delete ui;
}

#include "total.h"
#include "ui_total.h"

Total::Total(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Total)
{
    ui->setupUi(this);
    connect(ui->searchbutton, SIGNAL(clicked()), this, SLOT(getAll()));
}

void Total::getAll() {
    QString qdate = ui->textEdit->toPlainText();
    if (qdate == "") {
        // Clear Message
        ui->textBrowser->setText("");
        return;
    }
    string date = string((const char*)qdate.toLocal8Bit());

    // 判断日期格式
    bool error = checkDate(date);

    if (error) {
        ui->textBrowser->setText("Invalid Date Format!\nPlease try again.");
        return;
    }


    vector<orderList> data =  bookAccess.printTotalAndOrder(date);
    QString text;
    if (data.size() == 0) {
        text = "No sell record this month!";
    }
    else {
        for (unsigned int i = 0; i < data.size(); i++) {
            QString returnName = QString(QString::fromLocal8Bit(data[i].bookName.c_str()));
            QString returnNumber = QString(QString::fromLocal8Bit(data[i].sellNumberLastMonth.c_str()));
            QString returnMoney = QString(QString::fromLocal8Bit(data[i].totalMoneyLastMonth.c_str()));
            text += "Name: ";
            text += returnName;
            text += ", SellNumber: ";
            text += returnNumber;
            text += ", Gross: ";
            text += returnMoney;
            text += "\n";
        }
    }

    ui->textBrowser->setText(text);
}
Total::~Total()
{
    delete ui;
}

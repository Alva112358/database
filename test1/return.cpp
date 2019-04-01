#include "return.h"
#include "ui_return.h"

Return::Return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Return)
{
    ui->setupUi(this);
    connect(ui->submitbutton, SIGNAL(clicked()), this, SLOT(submit()));
}

/*
    输入书名，销售号，数量，进行退货
*/
void Return::submit() {
    QString qbookName = ui->BookName->toPlainText();
    QString qreceiptNumber = ui->ReceiptNumber->toPlainText();
    QString qbookNumber = ui->BookNumber->toPlainText();

    if (qbookName == "" || qreceiptNumber == "" || qbookNumber == "") {
        // Clear Message
        ui->textBrowser->setText("");
        return;
    }

    string bookName = string((const char*)qbookName.toLocal8Bit());
    string receiptNumber = string((const char*)qreceiptNumber.toLocal8Bit());
    string bookNumber = string((const char*)qbookNumber.toLocal8Bit());

    if (!checkIfNumbers(receiptNumber)) {
        ui->textBrowser->setText("Please input number in [Receipt Number]");
        return;
    }
    if (!checkIfNumbers(bookNumber)) {
        ui->textBrowser->setText("Please input number in [Book Number]");
        return;
    }
    returnInfo data =  bookAccess.returnBook(bookName, receiptNumber, bookNumber);
    QString returnID = QString(QString::fromLocal8Bit(data.returnId.c_str()));
    QString returnNumber = QString(QString::fromLocal8Bit(data.returnNumber.c_str()));
    QString returnDate = QString(QString::fromLocal8Bit(data.returnData.c_str()));
    QString returnName = QString(QString::fromLocal8Bit(data.returnName.c_str()));

    if (returnID == "-1") {
        QString text = "No sell record!";
        ui->textBrowser->setText(text);
    }
    else if (returnID == "-2") {
        QString text = "You can't return more than you've previously brought!";
        ui->textBrowser->setText(text);
    }
    else if (returnID == "-3") {
        QString text = "You have already returned before!\nSecond return is not allowed!";
        ui->textBrowser->setText(text);
    }
    else {
        QString text = "ID: " + returnID
                        + "\nName: " + returnName
                        + "\nNumber: " + returnNumber
                        + "\nDate: " + returnDate;

        ui->textBrowser->setText(text);
    }
}
Return::~Return()
{
    delete ui;
}

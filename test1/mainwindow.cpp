#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSize>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // BookAccess Database::bookAccess = BookAccess();
    ui->setupUi(this);
    connect(ui->purchase_button, SIGNAL(clicked()), this, SLOT(HandlePurchaseButton()));
    connect(ui->return_button, SIGNAL(clicked()), this, SLOT(HandleReturnButton()));
    connect(ui->total_button, SIGNAL(clicked()), this, SLOT(HandleTotalButton()));
    connect(ui->sale_button, SIGNAL(clicked()), this, SLOT(HandleSaleButton()));
    // Test database
    int num = bookAccess.getTotalBookNumber("DatabaseBook");
    cout << num << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSize MainWindow::sizeHint() const {
    return QSize(1000, 600);
}

void MainWindow::HandlePurchaseButton()
{
    //what you want to do
    purchasedialog = new MyDialog(this);
    purchasedialog->setModal(false);
    purchasedialog->show();
}

void MainWindow::HandleReturnButton() {
    //what you want to do
    returndialog = new Return(this);
    returndialog->setModal(false);
    returndialog->show();
}

void MainWindow::HandleTotalButton() {
    // what you want to do
    totaldialog = new Total(this);
    totaldialog->setModal(false);
    totaldialog->show();
}

void MainWindow::HandleSaleButton() {
    selldialog = new Sell(this);
    selldialog->setModal(false);
    selldialog->show();
}

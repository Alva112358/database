#include "purchase.h"
#include "ui_purchase.h"

Purchase::Purchase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Purchase)
{
    ui->setupUi(this);
}

Purchase::~Purchase()
{
    delete ui;
}

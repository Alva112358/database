#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <purchasedialog.h>
#include <return.h>
#include <sell.h>
#include <total.h>
#include <C:/mysql-5.7.20-winx64/include/mysql.h>
#include <database.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual QSize sizeHint() const;
public slots:
    void HandlePurchaseButton();
    void HandleReturnButton();
    void HandleTotalButton();
    void HandleSaleButton();

private:
    Ui::MainWindow *ui;
    MyDialog *purchasedialog;
    Return *returndialog;
    Sell *selldialog;
    Total *totaldialog;
};

#endif // MAINWINDOW_H

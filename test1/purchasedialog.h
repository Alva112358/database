#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <database.h>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();
public slots:
    void getBookStock();
    void submit();
private:
    Ui::MyDialog *ui;
    QPushButton *searchbutton;
    QPushButton *submitbutton;

};

#endif // MYDIALOG_H

#ifndef SELL_H
#define SELL_H

#include <QDialog>
#include <database.h>

namespace Ui {
class Sell;
}

class Sell : public QDialog
{
    Q_OBJECT

public:
    explicit Sell(QWidget *parent = 0);
    ~Sell();
public slots:
    void getBookStock();
    void sell();
private:
    Ui::Sell *ui;
};

#endif // SELL_H

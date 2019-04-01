#ifndef PURCHASE_H
#define PURCHASE_H

#include <QWidget>

namespace Ui {
class Purchase;
}

class Purchase : public QWidget
{
    Q_OBJECT

public:
    explicit Purchase(QWidget *parent = 0);
    ~Purchase();

private:
    Ui::Purchase *ui;
};

#endif // PURCHASE_H

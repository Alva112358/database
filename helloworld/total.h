#ifndef TOTAL_H
#define TOTAL_H

#include <QDialog>
#include <database.h>

namespace Ui {
class Total;
}

class Total : public QDialog
{
    Q_OBJECT

public:
    explicit Total(QWidget *parent = 0);
    ~Total();
public slots:
    void getAll();
private:
    Ui::Total *ui;
};

#endif // TOTAL_H

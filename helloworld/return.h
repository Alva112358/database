#ifndef RETURN_H
#define RETURN_H

#include <QDialog>
#include <database.h>

namespace Ui {
class Return;
}

class Return : public QDialog
{
    Q_OBJECT

public:
    explicit Return(QWidget *parent = 0);
    ~Return();
public slots:
    void submit();
private:
    Ui::Return *ui;
};

#endif // RETURN_H

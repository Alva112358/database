#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;
    w.setWindowTitle(QObject::tr("Book Manage System"));
    w.resize(800, 600);

    // add textbox
    /*
    QLineEdit edit;
    edit.setPlaceholderText(QObject::tr("Input"));
    edit.setGeometry(500,50,40,60);
    edit.show();
    edit.setParent(&w);
    */
    w.show();

    return a.exec();
}

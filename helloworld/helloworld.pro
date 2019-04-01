#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T00:03:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    BookAccess.cpp \
    database.cpp \
    purchasedialog.cpp \
    return.cpp \
    sell.cpp \
    total.cpp \
    mainwindow.cpp

HEADERS += \
    BookAccess.h \
    database.h \
    purchasedialog.h \
    return.h \
    sell.h \
    total.h \
    mainwindow.h

FORMS += \
    PurchaseDialog.ui \
    return.ui \
    sell.ui \
    total.ui \
    mainwindow.ui

LIBS += -LC:\MySQL_Connector_C_6.1\lib -llibmysql

RC_FILE += icotest.rc
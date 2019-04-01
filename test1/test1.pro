#-------------------------------------------------
#
# Project created by QtCreator 2018-06-26T18:17:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
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
        mainwindow.cpp \
    purchasedialog.cpp \
    return.cpp \
    sell.cpp \
    total.cpp \
    BookAccess.cpp \
    database.cpp

HEADERS += \
        mainwindow.h \
    purchasedialog.h \
    return.h \
    sell.h \
    total.h \
    BookAccess.h \
    database.h

FORMS += \
        mainwindow.ui \
    purchaseDialog.ui \
    return.ui \
    sell.ui \
    total.ui

#在windows下使用第三方库的方法
#C:\mysql-5.7.20-winx64\lib

LIBS += -LC:\MySQL_Connector_C_6.1\lib -llibmysql


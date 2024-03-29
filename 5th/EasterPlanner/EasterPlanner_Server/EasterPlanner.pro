#-------------------------------------------------
#
# Project created by QtCreator 2019-03-02T13:53:32
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasterPlanner
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

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    drawablemapwidget.cpp \
    server.cpp \
    client_conn.cpp \
    aboutdialog.cpp

HEADERS += \
        mainwindow.h \
    drawablemapwidget.h \
    dbmanager.h \
    person.h \
    coordinate.h \
    center.h \
    center.h \
    server.h \
    client_conn.h \
    aboutdialog.h

FORMS += \
        mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc

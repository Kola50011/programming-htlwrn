#-------------------------------------------------
#
# Project created by QtCreator 2019-04-27T15:02:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateFlightPlanner
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
    drawablemapwidget.cpp

HEADERS += \
        mainwindow.h \
    drawablemapwidget.h \
    database.h \
    airline.h \
    airport.h \
    route.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

copydata.commands = $(COPY_DIR) "$$PWD/static/AirlineRoutes.db" "$$OUT_PWD"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

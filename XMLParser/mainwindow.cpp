#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtXml>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDomDocument document("kurslisten");
    QFile file("kurslisten.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    document.setContent(&file);

    QDomElement domElement = document.documentElement();

    for (auto kurstermin = domElement.firstChild(); !kurstermin.isNull(); kurstermin = kurstermin.nextSibling()) {
        for (auto person = kurstermin.firstChild(); !person.isNull(); person = person.nextSibling()) {
            qDebug() << person.toElement().attribute("fname");
        }
    }

    file.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

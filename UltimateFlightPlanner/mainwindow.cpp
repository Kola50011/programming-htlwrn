#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QStringList>
#include "database.h"
#include "airport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList airportsList;
    for (auto &airport : Database::getInstance().airports)
    {
        airportsList.append(airport.name);
    }

    QCompleter *aiportsCompleter = new QCompleter(airportsList, this);
    aiportsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->startAirport->setCompleter(aiportsCompleter);
    ui->endAirport ->setCompleter(aiportsCompleter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

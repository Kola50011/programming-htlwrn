#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QStringList>
#include "database.h"
#include "airport.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<Airport>();
    qRegisterMetaType<Airline>();
    qRegisterMetaType<Route>();

    connect(this, &MainWindow::calculate_route, ui->map, &DrawableMapWidget::on_calculate_route_clicked);

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

void MainWindow::on_calculateButton_clicked()
{
    try {
        auto db = Database::getInstance();
        if (!ui->endAirport->text().isEmpty() && !ui->startAirport->text().isEmpty()
                && (ui->endAirport->text() != ui->startAirport->text())) {
            emit calculate_route(db.airport_for_name(ui->startAirport->text()), db.airport_for_name(ui->endAirport->text()));
        } else if (ui->endAirport->text().toStdString() == ui->startAirport->text().toStdString()) {
            QMessageBox mb;
            mb.setText("Start- and End-Airport can't be the same!");
            mb.exec();
        } else {
            QMessageBox mb;
            mb.setText("You have to fill out both text boxes to search for a route!");
            mb.exec();
        }
    } catch (const std::logic_error e) {
        qDebug() << e.what();
        QMessageBox mb;
        mb.setText("One of the airports was not found, please check your airport-input!");
        mb.exec();
    }
}

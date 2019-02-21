/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#include "addroutedialog.h"
#include "ui_addroutedialog.h"
#include <QCompleter>

AddRouteDialog::AddRouteDialog(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::AddRouteDialog)
{
    ui->setupUi(this);
    initGUI();
}

AddRouteDialog::~AddRouteDialog()
{
    delete ui;
}

void AddRouteDialog::initGUI()
{
    DbManager database = DbManager::getInstance();
    QStringList airportList;
    for (auto &airport : database.airports)
    {
        airportList << airport.name + " (" + airport.iata + ")";
    }
    QCompleter *aiportCompleter = new QCompleter(airportList, this);
    aiportCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->StartAirport->setCompleter(aiportCompleter);
    ui->EndAirport->setCompleter(aiportCompleter);

    // Airlines
    QStringList airlineList;
    for (auto &airline : database.airlines)
    {
        airlineList << airline.name;
    }
    QCompleter *airlineCompleter = new QCompleter(airlineList, this);
    airlineCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->Airline->setCompleter(airlineCompleter);
}

void AddRouteDialog::on_buttonBox_accepted()
{
    DbManager database = DbManager::getInstance();
    QString departure = ui->StartAirport->text().simplified();
    QString destination = ui->EndAirport->text().simplified();
    QString airline = ui->Airline->text().simplified();

    departure = departure.left(departure.indexOf("(") - 1);
    destination = destination.left(destination.indexOf("(") - 1);

    int airport1 = database.getAirportId(departure);
    int airport2 = database.getAirportId(destination);
    int airlineId = database.getAirlineId(airline);

    if (airport1 == 0 || airport2 == 0)
    {
        qDebug() << "Using debug mode";
        airport1 = 4908; // Vienna
        airport2 = 3699; // Palm Spings
    }

    DbManager::getInstance().addRoute(airport1, airport2, airlineId);

    ui->StartAirport->setText("");
    ui->EndAirport->setText("");
    ui->Airline->setText("");
}

void AddRouteDialog::on_buttonBox_rejected()
{
}

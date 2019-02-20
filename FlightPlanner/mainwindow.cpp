#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <future>
#include <QCompleter>
#include <chrono>
#include "customsearchalgorithm.h"
#include "breadthfirstsearchalgorithm.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGUI();
}

void MainWindow::initGUI()
{
    QStringList airportList;
    for (auto &airport : database.airports)
    {
        airportList << airport.name + " (" + airport.iata + ")";
    }
    QCompleter *aiportCompleter = new QCompleter(airportList, this);
    aiportCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->FromSearch->setCompleter(aiportCompleter);
    ui->ToSearch->setCompleter(aiportCompleter);

    // Airlines
    QStringList airlineList;
    for (auto &airline : database.airlines)
    {
        airlineList << airline.name;
    }
    QCompleter *airlineCompleter = new QCompleter(airlineList, this);
    airlineCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->AirlineSearch->setCompleter(airlineCompleter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillFlightTable(vector<vector<int>> routes)
{
    vector<QString> flights;
    for (auto &vec : routes)
    {
        QString flight;
        for (int i{0}; i <= vec.size() - 1; i++)
        {
            if (i != 0)
            {
                flight += " -> ";
            }
            QString airportName = database.getAirportName(vec[i]);
            flight += airportName;
        }
        flights.push_back(flight);
    }
    sort(flights.begin(), flights.end());
    for (auto &flight : flights)
    {
        ui->flighttable->addItem(new QListWidgetItem(flight));
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->flighttable->clear();
    ui->map->resetPic();

    QString departure = ui->FromSearch->text();
    QString destination = ui->ToSearch->text();
    QString airline = ui->AirlineSearch->text();

    departure = departure.left(departure.indexOf("(") - 1);
    destination = destination.left(destination.indexOf("(") - 1);

    int airport1 = database.getAirportId(departure);
    int airport2 = database.getAirportId(destination);
    int airlineId = database.getAirlineId(airline);

    airport1 = 4908; // Vienna
    airport2 = 3699; // Palm Spings

    BreadthFirstSearchAlgorithm customSearchAlgorithm;

    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<int>> routes = customSearchAlgorithm.getRoutes(airport1, airport2);
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

    fillFlightTable(routes);


    auto newRoutes = splitRoutes(routes, airlineId);
    if (airlineId == -1)
    {
        ui->map->connectTheDots(get<2>(newRoutes), QColor{82, 82, 255});
    }
    else
    {
        ui->map->connectTheDots(get<0>(newRoutes), QColor{255, 82, 82});
        ui->map->connectTheDots(get<1>(newRoutes), QColor{82, 82, 255});
        ui->map->connectTheDots(get<2>(newRoutes), QColor{82, 82, 82});
    }
}

std::tuple<vector<tuple<int, int>>, vector<tuple<int, int>>, vector<tuple<int, int>>> MainWindow::splitRoutes(vector<vector<int>> routes, int airline)
{
    vector<tuple<int, int>> airlineRoutes;
    vector<tuple<int, int>> allianceRoutes;
    vector<tuple<int, int>> otherRoutes;

    int alliance = database.airlines[airline].alliance;

    for (auto &route : routes)
    {
        for (int i{0}; i <= route.size() - 2; i++)
        {
            if (database.isConnected(route[i], route[i + 1], airline))
            {
                airlineRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
            else if (database.isConnectedViaAlliance(route[i], route[i + 1], alliance))
            {
                allianceRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
            else
            {
                otherRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
        }
    }

    return std::make_tuple(airlineRoutes, allianceRoutes, otherRoutes);
}

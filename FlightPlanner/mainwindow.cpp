#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <future>
#include <QCompleter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initComboBoxen();
}

void MainWindow::initComboBoxen()
{
    // Set departure and destination airport comboboxen
    QStringList airportList;
    for (auto &airport : database.airports)
    {
        airportList << airport.name;
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

vector<vector<int>> MainWindow::getRoutes(vector<int> prev, int depth, int start, int end)
{
    vector<vector<int>> ret;
    if (prev.size() == 0)
    {
        prev.push_back(start);
    }

    if (depth == 0)
    {
        if (database.isConnected(start, end))
        {
            vector<int> toAdd = prev;
            toAdd.push_back(end);
            ret.push_back(toAdd);
        }
    }
    else
    {
        auto nbs = database.getNeighbours(start);
        vector<future<vector<vector<int>>>> futs;

        for (auto &airport : nbs)
        {
            if (std::find(prev.begin(), prev.end(), airport) == prev.end())
            {
                vector<int> toAdd = prev;
                toAdd.push_back(airport);
                futs.push_back(std::async(launch::async, &MainWindow::getRoutes, this, toAdd, depth - 1, airport, end));
            }
        }

        for (auto &fut : futs)
        {
            auto toConcat = fut.get();
            ret.insert(ret.end(), toConcat.begin(), toConcat.end());
        }
    }
    return ret;
}

void MainWindow::on_pushButton_clicked()
{
    ui->flighttable->clear();

    QString departure = ui->FromSearch->text();
    QString destination = ui->ToSearch->text();
    QString airline = ui->AirlineSearch->text();

    int airport1 = database.getAirportId(departure);
    int airport2 = database.getAirportId(destination);
    //int airport1{4908};
    //int airport2{1305};

    int depth{0};
    vector<vector<int>> routes;
    do
    {
        routes = getRoutes({}, depth, airport1, airport2);
        depth += 1;

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
                airportName = airportName.simplified();
                flight += airportName;
            }
            ui->flighttable->addItem(new QListWidgetItem(flight));
        }
    } while (routes.size() == 0 && depth <= 10);

    ui->map->connectTheDots(routes);
}

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtDebug>
#include <vector>
#include <route.h>
#include <airport.h>
#include <airline.h>

class DbManager
{
  public:
    std::vector<std::vector<Route>> routes;
    std::vector<Airport> airports;
    std::vector<Airline> airlines;

    static DbManager &getInstance()
    {
        static DbManager instance;
        return instance;
    }

    int getAirportCount()
    {
        QSqlQuery query("select count(*) as amount from Airport");
        int amount = query.record().indexOf("amount");

        while (query.next())
        {
            return query.value(amount).toInt();
        }
    }

    int getAirlineCount()
    {
        QSqlQuery query("select count(*) as amount from Airline");
        int amount = query.record().indexOf("amount");

        while (query.next())
        {
            return query.value(amount).toInt();
        }
    }

    int getAirportId(QString name)
    {
        for (auto &airport : airports)
        {
            if (airport.name == name)
            {
                return airport.id;
            }
        }
        return 0;
    }

    bool isConnected(int id1, int id2)
    {
        for (auto &route : routes[id1])
        {
            if (route.end == id2)
            {
                return true;
            }
        }
        return false;
    }

    QString getAirportName(int id)
    {
        return airports[id].name;
    }

    std::vector<int> getNeighbours(int id)
    {
        std::vector<int> results;
        for (auto &route : routes[id])
        {
            if (std::find(results.begin(), results.end(), route.end) == results.end()) {
               results.push_back(route.end);
            }
        }
        return results;
    }

  private:
    QSqlDatabase m_db;

    DbManager()
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("/home/koka/workspace/programming-htlwrn/FlightPlanner/static/AirlineRoutes.db");

        if (!m_db.open())
        {
            qDebug() << "Error: connection with database fail";
        }
        else
        {
            qDebug() << "Database: connection ok";
        }

        loadRoutes();
        loadAirports();
        loadAirlines();
    }

    void loadRoutes()
    {
        routes.resize(getAirportCount());
        QSqlQuery query;
        query.prepare("select * from route order by airport1");
        query.exec();

        auto a1Col = query.record().indexOf("airport1");
        auto a2Col = query.record().indexOf("airport2");
        auto airlineCol = query.record().indexOf("airline");

        while (query.next())
        {
            int a1{query.value(a1Col).toInt()};
            routes[a1].push_back(Route(a1, query.value(a2Col).toInt(), query.value(airlineCol).toInt()));
        }
    }

    void loadAirports()
    {
        airports.resize(getAirportCount() + 1);
        QSqlQuery query;
        query.prepare("select * from airport");
        query.exec();

        auto idCol = query.record().indexOf("id");
        auto latitudeCol = query.record().indexOf("latitude");
        auto longitudeCol = query.record().indexOf("longitude");
        auto nameCol = query.record().indexOf("name");
        auto iataCol = query.record().indexOf("iata");

        while (query.next())
        {
            auto id{query.value(idCol).toInt()};
            airports.at(id) = Airport(id,
                                      query.value(latitudeCol).toDouble(), query.value(longitudeCol).toDouble(),
                                      query.value(nameCol).toString(), query.value(iataCol).toString());
        }
    }

    void loadAirlines()
    {
        airlines.resize(getAirlineCount() + 1);
        QSqlQuery query;
        query.prepare("select * from airline");
        query.exec();

        auto idCol = query.record().indexOf("id");
        auto nameCol = query.record().indexOf("name");
        auto allianceCol = query.record().indexOf("alliance");

        while (query.next())
        {
            auto id{query.value(idCol).toInt()};
            airlines.at(id) = Airline(id, query.value(nameCol).toString(), query.value(allianceCol).toInt());
        }
    }
};

#endif // DBMANAGER_H

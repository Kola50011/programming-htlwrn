#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <vector>
#include "airport.h"
#include "airline.h"
#include "route.h"
#include <memory>

using namespace std;

class Database
{

private:
    Database()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("AirlineRoutes.db");
        qDebug() << "DB is open:" << db.open();

        getAirports();
        get_airlines();
        get_routes();
    }

    void getAirports()
    {
        QSqlQuery query;
        if (!query.exec("select * from Airport;")) {
            qDebug() << "Error while querying db!";
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug() << query.executedQuery();
//            qDebug() << "Got" << query.size() << "Results!";
        }

        while (query.next())
        {
            Airport airport;
            airport.id = query.value("id").toInt();
            airport.latitude = query.value("latitude").toDouble();
            airport.longitude = query.value("longitude").toDouble();
            airport.name = query.value("name").toString().simplified();
            airport.iata = query.value("iata").toString();
            airports.push_back(airport);
        }

        qDebug() << airports.size() << "Airports loaded from db";
    }

    void get_airlines()
    {
        QSqlQuery query;
        if (!query.exec("select * from Airline;")) {
            qDebug() << "Error while querying the db!";
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug() << query.executedQuery();
//            qDebug() << "Got" << query.size() << "Results!";
        }

        while (query.next()) {
            Airline airline;
            airline.id = query.value("id").toInt();
            airline.name = query.value("id").toString();
            airline.alliance = query.value("alliance").toInt();
            airlines.push_back(airline);
        }

        qDebug() << airlines.size() << "Airlines loaded from db";
    }

    void get_routes() {
        QSqlQuery query;
        if (!query.exec("select * from Route;")) {
            qDebug() << "Error while querying the db!";
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug() << query.executedQuery();
//            qDebug() << "Got" << query.size() << "Results!";
        }

        while (query.next()) {
            Route route;
            route.airline = query.value("airline").toInt();
            route.start = query.value("airport1").toInt();
            route.end = query.value("airport2").toInt();
            routes.push_back(route);
        }

        qDebug() << routes.size() << "Routes loaded from db";
    }


public:

    static Database &getInstance()
    {
        static Database db;
        return db;
    }

    Airport& airport_for_id(int id) {
        for (auto& airport : airports) {
            if (airport.id == id) {
                return airport;
            }
        }
        throw logic_error("Airport with id " + std::to_string(id) + " not found!");
    }

    Airport& airport_for_name(QString name) {
        for (auto& airport : airports) {
            if (airport.name == name) {
                return airport;
            }
        }
        throw logic_error("Airport " + name.toStdString() + " not found!");
    }

    vector<Airport> airports;
    vector<Airline> airlines;
    vector<Route> routes;
};

#endif // DATABASE_H

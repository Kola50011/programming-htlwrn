#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <vector>
#include "airport.h"
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
    }

    void getAirports()
    {
        QSqlQuery query;
        if (!query.exec("select * from Airport;")) {
            qDebug() << "Error while querying db!";
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug() << query.executedQuery();
            qDebug() << "Got" << query.size() << "Results!";
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
    }


public:

    static Database &getInstance()
    {
        static Database db;
        return db;
    }

    vector<Airport> airports;
};

#endif // DATABASE_H

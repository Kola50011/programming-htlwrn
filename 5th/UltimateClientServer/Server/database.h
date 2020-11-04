#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "airport.h"

using namespace std;

class Database
{
private:
    Database()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./AirlineRoutes.db");

        qDebug() << "DB is open:" << db.open();

        getAirports();
    }

    vector<Airport> airports;

    void getAirports()
    {
        QSqlQuery query{"select * from Airport;"};
        query.exec();

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

        qDebug() << "Got " << airports.size() << " airports from db!";
    }

public:
    ~Database() {}

    static Database &getInstance()
    {
        static Database db;
        return db;
    }

    Airport getAirportFromIata(QString iata)
    {
        for (auto airport : airports)
        {
            if (airport.iata == iata)
            {
                return airport;
            }
        }
        return airports[0];
    }

    Airport getAirportFromIataSelect(QString iata)
    {
        QSqlQuery query;
        query.prepare("select * from airport where iata = :iata;");
        query.bindValue(":iata", iata);
        query.exec();

        if (query.next())
        {
            Airport airport;
            airport.id = query.value("id").toInt();
            airport.latitude = query.value("latitude").toDouble();
            airport.longitude = query.value("longitude").toDouble();
            airport.name = query.value("name").toString().simplified();
            airport.iata = query.value("iata").toString();
            return airport;
        }
        return Airport();
    }

    vector<QString> getPath(QString start, QString end)
    {
        vector<QString> ret;
        ret.push_back(getAirportFromIataSelect(start).name);
        ret.push_back("mid");
        ret.push_back("hi");
        ret.push_back(getAirportFromIataSelect(end).name);
        return ret;
    }
};

#endif // DATABASE_H

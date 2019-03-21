#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtDebug>
#include <vector>

#include "person.h"

using namespace std;

class DbManager
{
public:
    vector<Person> people;

    static DbManager &getInstance()
    {
        static DbManager instance;
        return instance;
    }

    void addPerson(QString name, double latitude, double longitude)
    {
        QSqlQuery query;
        query.prepare("replace into people values (?, ?, ?);");
        query.addBindValue(name);
        query.addBindValue(latitude);
        query.addBindValue(longitude);
        query.exec();
    }

    void addPerson(Person p) {
        addPerson(p.name, p.latitude, p.longitude);
    }

    double getRandomLatitude()
    {
      return fRand(47.786898, 47.846533);
    }

    double getRandomLongitude()
    {
        return fRand(16.209652, 16.281017);
    }

private:
  QSqlDatabase db;

  DbManager()
  {
      db = QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName("./Locations.db");

      if (!db.open())
      {
          qDebug() << "Error in connection with database";
      }
      else
      {
          qDebug() << "Database: connection ok";
      }

      loadPeople();
  }

  void loadPeople()
  {
    QSqlQuery createQuery;
    createQuery.exec("create table people "
              "(name varchar(64) primary key, "
              "latitude decimal(9,6), "
              "longitude decimal(9,6))");
    createQuery.exec("CREATE UNIQUE INDEX idx_name ON people (name);");

    for (int i{0}; i < 255; i++)
    {
        addPerson(QString::number(i), fRand(47.786898, 47.846533), fRand(16.209652, 16.281017));
    }

    QSqlQuery selectQuery;
    selectQuery.prepare("select * from people order by name");
    selectQuery.exec();
    while (selectQuery.next())
    {
        QString name{selectQuery.value("name").toString()};
        double latitude{selectQuery.value("latitude").toDouble()};
        double longitude{selectQuery.value("longitude").toDouble()};
        people.push_back(Person(name, latitude, longitude));
    }
  }

  double fRand(double fMin, double fMax)
  {
      double f = (double)rand() / RAND_MAX;
      return fMin + f * (fMax - fMin);
  }
};

#endif // DBMANAGER_H

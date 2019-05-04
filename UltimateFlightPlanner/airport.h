/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>
#include <QMetaType>
#include <QVector>

class Airport
{
public:
  int id;
  double latitude;
  double longitude;
  QString name;
  QString iata;
  QVector<Airport> connections;

  Airport(int _id, double _latitude, double _longitude, QString _name, QString _iata)
  {
    id = _id;
    latitude = _latitude;
    longitude = _longitude;
    name = _name;
    iata = _iata;
  }

  Airport() {}
  ~Airport() {}
};
Q_DECLARE_METATYPE(Airport)

#endif // AIRPORT_H

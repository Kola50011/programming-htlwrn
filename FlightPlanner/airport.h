#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

class Airport
{
  public:
    int id;
    double latitude;
    double longitude;
    QString name;
    QString iata;

    Airport(int _id, double _latitude, double _longitude, QString _name, QString _iata)
    {
        id = _id;
        latitude = _latitude;
        longitude = _longitude;
        name = _name;
        iata = _iata;
    };

    Airport() {}
};

#endif // AIRPORT_H

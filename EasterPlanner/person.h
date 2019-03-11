#ifndef PERSON_H
#define PERSON_H

#include <math.h>

using namespace std;

class Person {
public:
    QString name;
    long double latitude;
    long double longitude;

    Person(QString _name, long double _latitude, long double _longitude)
    {
        name = _name;
        latitude = _latitude;
        longitude = _longitude;
    }

    double getDistance(long double _lat, long double _long)
    {
        return powf( _lat - latitude, 2.0) +
               powf( _long - longitude, 2.0);
    }
};

#endif // PERSON_H

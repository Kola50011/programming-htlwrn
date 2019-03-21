/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#ifndef PERSON_H
#define PERSON_H

#include <math.h>
#include <QString>
#include <QMetaType>
#include <QPoint>

using namespace std;

class Person {
public:
    inline static double leftLong;
    inline static double rightLong;
    inline static double topLat;
    inline static double bottomLat;

    inline static double mapWidth;
    inline static double mapHeight;

    QString name;
    long double latitude;
    long double longitude;

    Person(QString _name, long double _latitude, long double _longitude)
    {
        name = _name;
        latitude = _latitude;
        longitude = _longitude;
    }

    static void setValues(double _leftLong, double _rightLong,
               double _topLat, double _bottomLat,
               double _mapWidth, double _mapHeight)
    {
        leftLong = _leftLong;
        rightLong = _rightLong;
        topLat = _topLat;
        bottomLat = _bottomLat;
        mapWidth = _mapWidth;
        mapHeight = _mapHeight;
    }

    double getDistance(long double _lat, long double _long)
    {
        return powf( _lat - latitude, 2.0) +
               powf( _long - longitude, 2.0);
    }

    QPoint toPoint()
    {
        return QPoint((longitude - leftLong) / (rightLong - leftLong) * mapWidth,
                      (latitude - topLat) / (bottomLat - topLat) * mapHeight);
    }

    Person() {}
    ~Person() {}
};

Q_DECLARE_METATYPE(Person);

#endif // PERSON_H

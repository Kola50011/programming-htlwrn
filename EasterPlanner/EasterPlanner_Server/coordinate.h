/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
    double latitude;
    double longitude;

    Coordinate(double _latitude, double _longitude)
    {
        latitude = _latitude;
        longitude = _longitude;
    }
};

#endif // COORDINATE_H

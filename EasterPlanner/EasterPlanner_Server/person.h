#ifndef PERSON_H
#define PERSON_H

class Person {
public:
    QString name;
    double latitude;
    double longitude;

    Person(QString _name, double _latitude, double _longitude)
    {
        name = _name;
        latitude = _latitude;
        longitude = _longitude;
    }
};

#endif // PERSON_H

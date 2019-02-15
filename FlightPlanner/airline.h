#ifndef AIRLINE_H
#define AIRLINE_H

#include <QString>

class Airline
{
  public:
    int id;
    QString name;
    int alliance;

    Airline(int _id, QString _name, int _alliance)
    {
        id = _id;
        name = _name;
        alliance = _alliance;
    }

    Airline() {}
};

#endif // AIRLINE_H

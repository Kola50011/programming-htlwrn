/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef AIRLINE_H
#define AIRLINE_H

#include <QString>
#include <QMetaType>

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
  ~Airline() {}
};
Q_DECLARE_METATYPE(Airline)

#endif // AIRLINE_H

/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <QMetaType>

class Route
{
public:
  int start;
  int end;
  int airline;

  Route(int _start, int _end, int _airline)
  {
    start = _start;
    end = _end;
    airline = _airline;
  }

  Route() {}
  ~Route() {}
};
Q_DECLARE_METATYPE(Route)

#endif // ROUTE_H

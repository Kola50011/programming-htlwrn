#ifndef ROUTE_H
#define ROUTE_H

#include <string>

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
};
#endif // ROUTE_H

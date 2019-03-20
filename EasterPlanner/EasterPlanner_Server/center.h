#ifndef CENTER_H
#define CENTER_H

#include <vector>
#include <person.h>
#include <algorithm>
#include <QDebug>
#include <QColor>
#include <QRect>

using namespace std;

class Center {
public:
    inline static double leftLong;
    inline static double rightLong;
    inline static double topLat;
    inline static double bottomLat;
    inline static double mapWidth;
    inline static double mapHeight;

    double latitude;
    double longitude;

    QColor col;

    vector<Person> people;

    Center(double _latitude, double _longitude, QColor _col)
    {
        latitude = _latitude;
        longitude = _longitude;
        col = _col;
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

    bool hasPerson(Person &person)
    {
        for (Person &element : people)
        {
            if (element.name == person.name)
            {
                return true;
            }
        }
        return false;
    }

    bool addPerson(Person &person)
    {
        for (Person &element : people)
        {
            if (element.name == person.name)
            {
                return false;
            }
        }
        people.push_back(person);
        return true;
    }

    bool removePerson(Person &person)
    {
        for (auto iter = people.begin(); iter != people.end();)
        {
            if (iter->name == person.name)
            {
                iter = people.erase(iter);
                return true;
            }
            ++iter;
        }
        return false;
    }

    bool adjustCenter()
    {
        bool res = false;

        double newLat{0};
        double newLong{0};
        for (Person &person : people)
        {
            newLat += person.latitude;
            newLong += person.longitude;
        }

        if (people.size() > 0)
        {
            newLat = newLat / people.size();
            newLong = newLong / people.size();
        }

        if (newLat != latitude || newLong != longitude)
        {
            res = true;
        }

        latitude = newLat;
        longitude = newLong;

        return res;
    }

    QPoint toPoint()
    {
        return QPoint((longitude - leftLong) / (rightLong - leftLong) * mapWidth,
                      (latitude - topLat) / (bottomLat - topLat) * mapHeight);
    }

    QRect get_bounding_box() {
        int x_min = INT_MAX;
        int x_max = INT_MIN;
        int y_min = INT_MAX;
        int y_max = INT_MIN;

        for (Person& person : people) {
            QPoint p = person.toPoint();
            if (p.x() < x_min) {
                x_min = p.x();
            }
            if (p.x() > x_max) {
                x_max = p.x();
            }
            if (p.y() < y_min) {
                y_min = p.y();
            }
            if (p.y() > y_max) {
                y_max = p.y();
            }
        }

        QPoint min_p{x_min, y_min};
        QPoint max_p{x_max, y_max};


        return QRect{min_p, max_p};
    }
};

#endif // CENTER_H

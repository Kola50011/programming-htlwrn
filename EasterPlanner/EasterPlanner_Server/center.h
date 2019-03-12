#ifndef CENTER_H
#define CENTER_H

#include <vector>
#include <person.h>
#include <algorithm>
#include <QDebug>

using namespace std;

class Center {
public:
    double latitude;
    double longitude;

    vector<Person> people;

    Center(double _latitude, double _longitude)
    {
        latitude = _latitude;
        longitude = _longitude;
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
};

#endif // CENTER_H

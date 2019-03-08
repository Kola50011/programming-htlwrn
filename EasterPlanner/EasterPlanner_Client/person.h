#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include "json.hpp"

using json = nlohmann::json;

class person {
public:
    QString name;
    double latitude;
    double longitude;

    person(QString _name, double _latitude, double _longitude)
    {
        name = _name;
        latitude = _latitude;
        longitude = _longitude;
    }

    json to_json() {
        return {
            {"name", name.toStdString()},
            {"lat", latitude},
            {"lon", longitude}
        };
    }
};


#endif // PERSON_H

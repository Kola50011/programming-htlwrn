#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <optional>
#include <QJsonObject>


class person {
public:
    QString name;
    double latitude;
    double longitude;

    person() {}

    QJsonObject to_json() {
        return {
            {"name", name},
            {"lat", latitude},
            {"lon", longitude}
        };
    }

    static bool from(QString _name, double _lat, double _lon, person& p) {
        if (_lon <= 16.209652 || _lon >= 16.281017) {
            return false;
        }

        if (_lat <= 47.786898 || _lat >= 47.846533) {
            return false;
        }

        if (_name.isEmpty()) {
            return false;
        }

        p = person{_name, _lat, _lon};
        return true;
    }
private:
    person(QString _name, double _latitude, double _longitude)
    {
        name = _name;
        latitude = _latitude;
        longitude = _longitude;
    }
};


#endif // PERSON_H

#include "point.h"

Point::Point(QPoint _point, QColor _color) : point{_point}, color{_color}
{
}

Point::Point() {}

QDataStream &operator <<(QDataStream &out, const Point &point) {
    out << point.point << point.color;
    return out;
}

QDataStream &operator >>(QDataStream &in, Point &point) {
    QPoint qPoint;
    QColor qColor;
    in >> qPoint >> qColor;
    point = Point(qPoint, qColor);
    return in;
}


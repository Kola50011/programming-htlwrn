#ifndef POINT_H
#define POINT_H

#include <QPoint>
#include <QColor>

class Point
{
public:
    Point();
    Point(QPoint _point, QColor _color);
    QPoint point;
    QColor color;

    friend QDataStream &operator <<(QDataStream &out, const Point &point);
    friend QDataStream &operator >>(QDataStream &in, Point &point);
};

#endif // POINT_H

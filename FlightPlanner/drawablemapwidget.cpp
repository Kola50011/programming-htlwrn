/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#include "drawablemapwidget.h"

#include "mainwindow.h"
#include <algorithm>

#include <cmath>

#include <QStringList>
#include <QPainter>
#include <QApplication>

DrawableMapWidget::DrawableMapWidget(QWidget *parent) : QWidget(parent)
{
    resetPic();
}

void DrawableMapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter{this};
    painter.drawPixmap(0, 0, pic);
}

QPoint DrawableMapWidget::airportToImg(Airport airport)
{
    return latLonToPoint(airport.latitude, airport.longitude);
}

QPoint DrawableMapWidget::latLonToPoint(double lat, double lon)
{
    return QPoint((lon + 180.0) * 4.0,
                  (lat - 90.0) * -4.0);
}
void DrawableMapWidget::connectAirports(Airport from, Airport to, QColor color, QPainter &painter)
{
    auto fromPoint = airportToImg(from);
    auto toPoint = airportToImg(to);

    auto directDistance = abs(from.longitude - to.longitude);
    auto roundDistance = 360 - directDistance;

    if (directDistance < roundDistance)
    {
        painter.setPen(QPen{QBrush{color}, 1});
        painter.drawLine(fromPoint, toPoint);
    }
    else
    {
        painter.setPen(QPen{QBrush{color}, 1});

        auto leftSide = latLonToPoint((from.latitude + to.latitude) / 2, -180.0);
        auto rightSide = latLonToPoint((from.latitude + to.latitude) / 2, 180.0);

        if (from.longitude > 0)
        {
            painter.drawLine(fromPoint, rightSide);
            painter.drawLine(leftSide, toPoint);
        }
        else
        {
            painter.drawLine(fromPoint, leftSide);
            painter.drawLine(rightSide, toPoint);
        }
    }
}

void DrawableMapWidget::connectTheDots(std::vector<tuple<int, int>> routes, QColor color)
{
    auto airports = DbManager::getInstance().airports;
    QPainter painter{&pic};

    // Need to go twice, as lines would be over text
    for (auto route : routes)
    {
        auto fromAirport = airports[std::get<0>(route)];
        auto toAirport = airports[std::get<1>(route)];

        connectAirports(fromAirport, toAirport, color, painter);
    }

    for (auto route : routes)
    {
        auto fromAirport = airports[std::get<0>(route)];
        auto toAirport = airports[std::get<1>(route)];

        auto fromPoint = airportToImg(fromAirport);
        auto toPoint = airportToImg(toAirport);

        painter.setPen(QPen{QBrush{QColor{0, 0, 0}}, 6});
        painter.drawText(fromPoint, fromAirport.iata);
        painter.drawText(toPoint, toAirport.iata);
    }

    update();
}

void DrawableMapWidget::resetPic()
{
    QPixmap l_pic{1440, 720};
    QPainter painter(&l_pic);
    QPixmap map("/home/koka/workspace/programming-htlwrn/FlightPlanner/static/Earthmap.jpg");
    map = map.scaled(1440, 720, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, map);

    painter.setPen(QPen{QBrush{QColor{0, 255, 0, 200}}, 3});

    for (auto airport : DbManager::getInstance().airports)
    {
        painter.drawPoint(airportToImg(airport));
    }

    pic = l_pic;
}

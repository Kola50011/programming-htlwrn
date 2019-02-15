/*
 * Author: KÃ¶nigsreiter Simon, Klimont Joel, Lampalzer Alexander, Glavanits Marcel
 * Class: 5BHIF
 * Date: 14.02.2019
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

std::tuple<double, double> DrawableMapWidget::latLonToImg(double lat, double lon)
{
    return std::make_tuple<double, double>((lat - 90.0) * -4.0, (lon + 180.0) * 4.0);
}

std::tuple<double, double> DrawableMapWidget::latLonToImg(std::tuple<double, double, double> inp)
{
    return latLonToImg(std::get<1>(inp), std::get<2>(inp));
}

void DrawableMapWidget::connectTheDots(std::vector<tuple<int, int>> routes, QColor color)
{
    auto airports = DbManager::getInstance().airports;
    QPainter painter{&pic};
    painter.setPen(QPen{QBrush{color}, 3});

    for (auto route : routes)
    {
        auto fromTuple = latLonToImg(airports[std::get<0>(route)].latitude, airports[std::get<0>(route)].longitude);
        auto toTuple = latLonToImg(airports[std::get<1>(route)].latitude, airports[std::get<1>(route)].longitude);

        QPoint from{int(std::round(std::get<1>(fromTuple))), int(std::round(std::get<0>(fromTuple)))};
        QPoint to{(int(std::round(std::get<1>(toTuple)))), int(std::round(std::get<0>(toTuple)))};

        painter.drawLine(from, to);
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

    auto airports = DbManager::getInstance().airports;
    for (auto airport : airports)
    {
        auto imgCoord = latLonToImg(airport.latitude, airport.longitude);
        int lat = int(std::round(std::get<0>(imgCoord)));
        int lon = int(std::round(std::get<1>(imgCoord)));

        painter.drawPoint(QPoint{lon, lat});
    }

    pic = l_pic;
}

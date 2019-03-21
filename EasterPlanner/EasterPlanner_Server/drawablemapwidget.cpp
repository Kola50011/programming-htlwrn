/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#include "drawablemapwidget.h"
#include "mainwindow.h"
#include "dbmanager.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <QStringList>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include "person.h"
#include "center.h"

DrawableMapWidget::DrawableMapWidget(QWidget *parent) : QWidget(parent)
{
    resetPic();

    double leftLong{16.209652};
    double rightLong{16.281017};
    double topLat{47.846533};
    double bottomLat{47.786898};

    Person::setValues(leftLong, rightLong,
                topLat, bottomLat,
                mapHeight, mapWidth);

    Center::setValues(leftLong, rightLong,
                      topLat, bottomLat,
                      mapHeight, mapWidth);
}

void DrawableMapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter{this};
    painter.drawPixmap(0, 0, pic);
}

void DrawableMapWidget::drawPeople(vector<Person> &people, QColor color)
{
    QPainter painter{&pic};
    for (int i{0}; i < people.size() - 1; i++)
    {
        painter.setPen(QPen{QBrush{color}, 15});
        painter.drawPoint(people[i].toPoint());
        //painter.setPen(QPen{QBrush{color}, 5});
        //painter.drawLine(people[i].toPoint(), people[i + 1].toPoint());
    }
    painter.setPen(QPen{QBrush{color}, 15});
    painter.drawPoint(people[people.size() - 1].toPoint());
    update();
}

void DrawableMapWidget::drawCenter(Center &center, QColor color)
{
    QPainter painter{&pic};
    painter.setPen(QPen{QBrush{color}, 30});
    QRect rect;
    rect.setWidth(10);
    rect.setHeight(10);
    rect.moveCenter(center.toPoint());
    painter.drawEllipse(rect);
    update();
}

void DrawableMapWidget::connectPeople(vector<Person> &people, QColor color)
{
    QPainter painter{&pic};
    for (int i{0}; i < people.size() - 1; i++)
    {
//        painter.setPen(QPen{QBrush{color}, 15});
//        painter.drawPoint(people[i].toPoint());
        painter.setPen(QPen{QBrush{color}, 5});
        painter.drawLine(people[i].toPoint(), people[i + 1].toPoint());
    }
//    painter.setPen(QPen{QBrush{color}, 15});
//    painter.drawPoint(people[people.size() - 1].toPoint());
    update();
}

void DrawableMapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked(event->x(), event->y());
}

void DrawableMapWidget::resetPic()
{
    QPixmap map(":/static/Stadtplan.jpg");
    map = map.scaledToHeight(720, Qt::SmoothTransformation);

    QPixmap l_pic{map.width(), 720};
    QPainter painter(&l_pic);

    painter.drawPixmap(0, 0, map);

    mapWidth = map.width();
    mapHeight = map.height();
    pic = l_pic;

    //vector<Person> people = DbManager::getInstance().people;
    //drawPeople(people, QColor{0, 0, 255, 255});
}

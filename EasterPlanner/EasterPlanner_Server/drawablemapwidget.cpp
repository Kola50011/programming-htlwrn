/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
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

DrawableMapWidget::DrawableMapWidget(QWidget *parent) : QWidget(parent)
{
    resetPic();
}

void DrawableMapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter{this};
    painter.drawPixmap(0, 0, pic);
}

QPoint DrawableMapWidget::personToPoint(Person &person)
{
    return QPoint((person.longitude - leftLong) / (rightLong - leftLong) * mapWidth,
                  (person.latitude - topLat) / (bottomLat - topLat) * mapHeight);
}

QPoint DrawableMapWidget::centerToPoint(Center &center)
{
    return QPoint((center.longitude - leftLong) / (rightLong - leftLong) * mapWidth,
                  (center.latitude - topLat) / (bottomLat - topLat) * mapHeight);

}

void DrawableMapWidget::drawPeople(vector<Person> &people, QColor color)
{
    QPainter painter{&pic};
    for (int i{0}; i < people.size() - 1; i++)
    {
        painter.setPen(QPen{QBrush{color}, 15});
        painter.drawPoint(personToPoint(people[i]));
        painter.setPen(QPen{QBrush{color}, 5});
        painter.drawLine(personToPoint(people[i]), personToPoint(people[i + 1]));
    }
    painter.setPen(QPen{QBrush{color}, 15});
    painter.drawPoint(personToPoint(people[people.size() - 1]));
    update();
}

void DrawableMapWidget::drawCenter(Center &center, QColor color)
{
    QPainter painter{&pic};
    painter.setPen(QPen{QBrush{color}, 30});
    QRect rect;
    rect.setWidth(10);
    rect.setHeight(10);
    rect.moveCenter(centerToPoint(center));
    painter.drawEllipse(rect);
    update();
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

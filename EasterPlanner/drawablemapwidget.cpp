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

QPoint DrawableMapWidget::personToPoint(Person person)
{
    return QPoint((person.longitude - leftLong) / (rightLong - leftLong) * mapWidth,
                  (person.latitude - bottomLat) / (topLat - bottomLat) * mapHeight);
}

void DrawableMapWidget::drawPeople(vector<Person> &people, QColor color)
{
    QPainter painter{&pic};
    painter.setPen(QPen{QBrush{color}, 6});
    for (Person person : people)
    {
        painter.drawPoint(personToPoint(person));
    }
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

    vector<Person> people = DbManager::getInstance().people;
    drawPeople(people, QColor{0, 0, 255, 255});
}

/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef DRAWABLEMAPWIDGET_H
#define DRAWABLEMAPWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QPoint>
#include <QColor>
#include <QPainter>

#include "center.h"
#include "person.h"
#include "dbmanager.h"
#include <vector>

class DrawableMapWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DrawableMapWidget(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *e);
  void resetPic();

  QPoint personToPoint(Person &person);
  QPoint centerToPoint(Center &center);
  void drawPeople(vector<Person> &people, QColor color);
  void drawCenter(Center &center, QColor color);
signals:

public slots:

private:
  double leftLong{16.209652};
  double rightLong{16.281017};
  double topLat{47.846533};
  double bottomLat{47.786898};

  double mapWidth;
  double mapHeight;
  QPixmap pic;
};

#endif // DRAWABLEMAPWIDGET_H

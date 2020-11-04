/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef DRAWABLEMAPWIDGET_H
#define DRAWABLEMAPWIDGET_H

#include <QWidget>
#include "dbmanager.h"
#include <QApplication>
#include <QPoint>

class DrawableMapWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DrawableMapWidget(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *e);
  QPoint airportToImg(Airport airport);
  QPoint latLonToPoint(double lat, double lon);

  void connectAirports(Airport from, Airport to, QColor color, QPainter &painter);
  void connectTheDots(std::vector<std::tuple<int, int>> routes, QColor color);

  void resetPic();
signals:

public slots:

private:
  QPixmap pic;
};

#endif // DRAWABLEMAPWIDGET_H

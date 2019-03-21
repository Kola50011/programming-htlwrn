/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
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
  void connectPeople(vector<Person>& people, QColor color);
signals:
  void clicked(int x, int y);

public slots:

private:
  double mapWidth;
  double mapHeight;
  QPixmap pic;

  // QWidget interface
protected:
  virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // DRAWABLEMAPWIDGET_H

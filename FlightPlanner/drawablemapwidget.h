/*
 * Author: KÃ¶nigsreiter Simon, Klimont Joel, Lampalzer Alexander, Glavanits Marcel
 * Class: 5BHIF
 * Date: 14.02.2019
 */

#ifndef DRAWABLEMAPWIDGET_H
#define DRAWABLEMAPWIDGET_H

#include <QWidget>
#include "dbmanager.h"
#include <QApplication>

class DrawableMapWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit DrawableMapWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);
    std::tuple<double, double> latLonToImg(double lat, double lon);
    std::tuple<double, double> latLonToImg(std::tuple<double, double, double> inp);

    void connectTheDots(std::vector<std::tuple<int, int>> routes, QColor color);

  signals:

  public slots:

  private:
    QPixmap pic;

    void resetPic();
};

#endif // DRAWABLEMAPWIDGET_H

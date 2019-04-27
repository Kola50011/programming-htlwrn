#include "drawablemapwidget.h"
#include <vector>
#include <QDebug>

#define WIDTH 1440
#define HEIGHT 720

using namespace std;

DrawableMapWidget::DrawableMapWidget(QWidget *parent) : QWidget(parent)
{
    resetPic();
}

void DrawableMapWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paint";
    QPainter painter{this};
    painter.drawPixmap(0, 0, pixmap);
}

QPoint DrawableMapWidget::airportToPoint(Airport &airport)
{
    return QPoint{
        (airport.longitude + 180.0) * (WIDTH / 360.0),
        (airport.latitude  - 90.0 ) * -(HEIGHT / 180.0)
    };
}

void DrawableMapWidget::resetPic()
{
    QPixmap l_pic{WIDTH, HEIGHT};
    QPainter painter(&l_pic);
    QPixmap map(":/static/static/Earthmap.jpg");
    map = map.scaled(WIDTH, HEIGHT, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, map);

    painter.setPen(QPen{QBrush{QColor{0, 255, 0, 200}}, 3});

    for (auto airport : Database::getInstance().airports)
    {
        QPoint point = airportToPoint(airport);
        qDebug() << point.y();
        painter.drawPoint(airportToPoint(airport));
    }

    pixmap = l_pic;
}

#ifndef DRAWABLEMAPWIDGET_H
#define DRAWABLEMAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include "database.h"
#include "airport.h"
#include "airline.h"

class DrawableMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawableMapWidget(QWidget *parent = nullptr);

protected:
     void paintEvent(QPaintEvent *event) override;

signals:

public slots:

private:

    QPoint airportToPoint(Airport& airport);
    void resetPic();
    QPixmap pixmap;
};

#endif // DRAWABLEMAPWIDGET_H

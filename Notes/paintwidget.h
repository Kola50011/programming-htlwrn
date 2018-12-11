#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <vector>
#include <QVector>
#include <QImage>
#include <QResizeEvent>
#include <QSize>
#include "point.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void drawPoints(QVector<Point> _points);
    QVector<Point> points;
    QColor penColor = Qt::black;

signals:
    void clicked();

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void resizeImage(QImage *image, const QSize &newSize);

    bool painting;
    int penWidth = 10;
    QImage image;
};

#endif // PAINTWIDGET_H

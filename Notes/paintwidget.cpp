#include "paintwidget.h"
#include <QRectF>
#include <iostream>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void PaintWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        painting = true;
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (painting) {
        points.push_back(Point(event->pos(), penColor));

        QPainter painter(&image);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));

        QPoint point = event->pos();
        painter.drawPoint(point.x(), point.y());
        update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        painting = false;
    }
    emit(clicked());
}

void PaintWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    points.clear();
    update();
}

void PaintWidget::drawPoints(QVector<Point> _points) {
    points = _points;
    QPainter painter(&image);
    foreach (Point point, points) {
        painter.setPen(QPen(point.color, penWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawPoint(point.point);
    }
    update();
}

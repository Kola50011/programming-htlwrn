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

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

signals:

public slots:

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
    QColor penColor = Qt::black;
    QVector<QPoint> points;
    QImage image;
};

#endif // PAINTWIDGET_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "airport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void calculate_route(Airport& start, Airport& end);

private slots:
    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbmanager.h>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, int port = 6969);
    ~MainWindow();

private slots:
    void on_clusterButton_clicked();

private:
    Ui::MainWindow *ui;
    DbManager database = DbManager::getInstance();
    server s;
};

#endif // MAINWINDOW_H

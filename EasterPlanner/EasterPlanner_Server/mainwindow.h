#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbmanager.h>
#include "server.h"
#include "center.h"

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

public slots:
    void dmw_clicked(int x, int y);

private:
    Ui::MainWindow *ui;
    DbManager database = DbManager::getInstance();
    server s;
    vector<Center> center_objs;
};

#endif // MAINWINDOW_H

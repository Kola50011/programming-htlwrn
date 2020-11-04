/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbmanager.h>
#include "server.h"
#include "center.h"
#include "aboutdialog.h"

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

    void on_actionInfo_triggered();

public slots:
    void dmw_clicked(int x, int y);
    void slider_moved(int val);

private:
    Ui::MainWindow *ui;
    AboutDialog abd;
    DbManager database = DbManager::getInstance();
    server s;
    vector<Center> center_objs;
};

#endif // MAINWINDOW_H

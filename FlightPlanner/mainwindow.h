/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include "dbmanager.h"
#include <QMessageBox>
#include <vector>
#include <QTableWidgetItem>
#include <memory>
#include "addroutedialog.h"

using namespace std;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  void initGUI();
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_actionAbout_triggered();

  void on_actionAdd_Route_triggered();

  void on_multiSearchButton_clicked();

private:
  Ui::MainWindow *ui;
  AddRouteDialog addRouteDialog;
  DbManager database = DbManager::getInstance();

  QFont titleFont{"Helvetica", 18, QFont::Bold};
  QFont standardFont{"Helvetica", 18};

  void fillFlightTable(vector<vector<int>> routes, bool sort);
  std::tuple<vector<tuple<int, int>>, vector<tuple<int, int>>, vector<tuple<int, int>>> splitRoutes(vector<vector<int>> routes, int airline);
};

#endif // MAINWINDOW_H

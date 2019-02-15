#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include "dbmanager.h"
#include <QMessageBox>
#include <vector>
#include <QTableWidgetItem>
#include <memory>

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
    void initComboBoxen();
    ~MainWindow();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::MainWindow *ui;
    DbManager database = DbManager::getInstance();

    QFont titleFont{"Helvetica", 18, QFont::Bold};
    QFont standardFont{"Helvetica", 18};

    vector<vector<int>> getRoutes(vector<int> prev, int depth, int start, int end);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionSettings_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QString host{"localhost"};
    QString port{"6969"};
    AboutDialog abd;
};

#endif // MAINWINDOW_H

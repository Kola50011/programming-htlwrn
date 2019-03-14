#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    QString host{"localhost"};
    QString port{"6969"};
};

#endif // MAINWINDOW_H

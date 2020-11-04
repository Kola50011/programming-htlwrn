#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QStringList>
#include <QMessageBox>
#include <QLabel>

#include <QtXml>

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
    void on_actionAbout_triggered();

    void on_pushButton_clicked();

public slots:
    void on_ready_read();

private:
    Ui::MainWindow *ui;
    QTcpSocket* sock;
};

#endif // MAINWINDOW_H

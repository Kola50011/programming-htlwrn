#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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
    void on_sendBtn_clicked();
    void on_data_received();

private:
    Ui::MainWindow *ui;
    bool connected = false;
    QTcpSocket* sock;
};

#endif // MAINWINDOW_H

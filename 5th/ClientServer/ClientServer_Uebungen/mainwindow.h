#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

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
    void on_new_connection();

public slots:
    void on_sql_received(QString sql);

signals:
    void sql_reply(QString repl);

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
};

#endif // MAINWINDOW_H

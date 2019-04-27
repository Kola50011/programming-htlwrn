#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>

#include <iostream>
#include "serversocket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6969);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::on_new_connection);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    qDebug() << "DB is open: " << db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_new_connection()
{
    qDebug() << "Got a new connection!";
    QTcpSocket* _sock = server->nextPendingConnection();
    ServerSocket* ss = new ServerSocket{_sock};
    connect(ss, &ServerSocket::sql_from_client_received, this, &MainWindow::on_sql_received);
    connect(this, &MainWindow::sql_reply, ss, &ServerSocket::sql_reply_receiver);
    ss->start();
}

void MainWindow::on_sql_received(QString sql)
{
    qDebug() << sql;

    QSqlQuery query;
    query.prepare(sql);
    bool execution = query.exec();
    QSqlRecord rec = query.record();

    QString ret;
    if (execution) {
        ret = QString::fromStdString("Operation was successful! " + std::to_string(rec.count()) + " values affected!");
    } else {
        ret = "Operation failed!";
    }
    emit sql_reply(ret);

}

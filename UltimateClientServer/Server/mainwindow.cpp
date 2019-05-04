#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "database.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress::Any, 4242);

    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    qDebug() << "New conntection!";
    QTcpSocket *socket = tcpServer->nextPendingConnection();
    socket->waitForReadyRead();

    QJsonObject jsonObject = QJsonDocument::fromJson(socket->readAll()).object();
    QString start = jsonObject["start"].toString();
    QString end = jsonObject["end"].toString();

    auto database = Database::getInstance();
    vector<QString> route = database.getPath(start, end);

    QJsonArray routeArray;
    for (auto node : route)
    {
        routeArray.push_back(node);
    }

    QJsonObject toSend;
    toSend["route"] = routeArray;

    socket->write((new QJsonDocument{toSend})->toJson());
    socket->flush();
    socket->close();
}

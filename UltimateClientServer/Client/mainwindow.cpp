#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 4242);
    if (socket->waitForConnected())
    {
        qDebug() << "Connected to host";
    } else
    {
        qDebug() << "Connection failed";
        return;
    }

    QJsonObject toSend;
    toSend["start"] = ui->startEdit->text();
    toSend["end"] = ui->startEdit->text();

    socket->write((new QJsonDocument{toSend})->toJson());
    socket->flush();
    socket->waitForReadyRead();

    QString reply = socket->readAll();
    qDebug() << "Got reply from server: " << reply;
    QJsonObject replyObject = QJsonDocument::fromJson(reply.toStdString().data()).object();
    QJsonArray routeArray = replyObject["route"].toArray();

    ui->resultEdit->setText("");
    for (auto node :  routeArray)
    {
        ui->resultEdit->append(node.toString());
    }
    socket->close();
}

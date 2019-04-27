#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QDebug>

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

void MainWindow::on_sendBtn_clicked()
{

    if (!connected) {
        sock = new QTcpSocket();
        sock->connectToHost(ui->hostInput->text(), ui->portInput->text().toInt());
        if (sock->waitForConnected()) {
            qDebug() << "Successfully connected!";
            connected = true;
            connect(sock, &QTcpSocket::readyRead, this, &MainWindow::on_data_received);
        } else {
            qDebug() << "Failed!";
        }
    }

    sock->write(ui->sqlInput->text().toStdString().data());
    sock->flush();

}

void MainWindow::on_data_received()
{
    QString repl = sock->readAll().toStdString().data();
    qDebug() << repl;
    ui->messages->append(repl);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "person.h"
#include "server_port.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>

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

void MainWindow::on_pushButton_clicked()
{
    double _lat{ui->latLineEdit->text().toDouble()};
    double _lon{ui->lonLineEdit->text().toDouble()};
    QString name = ui->nameLineEdit->text();

    person p;
    if (!person::from(name, _lat, _lon, p)) {
        QMessageBox mb;
        mb.setText("Your input was invalid!");
        mb.exec();
        return;
    }

    server_port* sp = new server_port(this);
    sp->exec();
    auto host{sp->get_host()};
    auto port{sp->get_port()};

    QTcpSocket sock{this};
    sock.connectToHost(host, port);
    if (sock.waitForConnected()) {
        sock.write(QJsonDocument{p.to_json()}.toJson());
        sock.flush();
    } else {
        QMessageBox eb;
        eb.setText("Error connecting to host!");
        eb.exec();
    }
}

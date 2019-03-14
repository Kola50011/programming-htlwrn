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

    QTcpSocket sock{this};
    sock.connectToHost(host, port.toInt());
    if (sock.waitForConnected()) {
        sock.write(QJsonDocument{p.to_json()}.toJson());
        sock.flush();
    } else {
        QMessageBox eb;
        eb.setText("Error connecting to host!");
        eb.exec();
    }
}

void MainWindow::on_actionSettings_triggered()
{

    server_port* sp = new server_port(host, port, this);
    sp->exec();

}

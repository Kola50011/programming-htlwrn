#include "server_port.h"
#include "ui_server_port.h"

server_port::server_port(QString& host, QString& port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_port)
{
    ui->setupUi(this);
    ui->serverLineEdit->setText(host);
    ui->portLineEdit->setText(port);
}

server_port::~server_port()
{
    delete ui;
}

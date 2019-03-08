#include "server_port.h"
#include "ui_server_port.h"

server_port::server_port(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_port)
{
    ui->setupUi(this);
}

server_port::~server_port()
{
    delete ui;
}

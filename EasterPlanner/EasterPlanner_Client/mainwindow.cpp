#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "person.h"
#include "server_port.h"

#include <QMessageBox>

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

    person p{name, _lat, _lon};

    server_port* sp = new server_port(this);
    sp->show();
}

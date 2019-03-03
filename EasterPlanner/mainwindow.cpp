#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "coordinate.h"
#include "person.h"
#include "dbmanager.h"

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

void MainWindow::on_clusterButton_clicked()
{
    DbManager database = DbManager::getInstance();
    vector<Person> people = database.people;
    vector<Coordinate> centers;

    for (int i{1}; i <= ui->amountEdit->text().toInt(); i++)
    {
        centers.push_back(Coordinate(database.getRandomLatitude(), database.getRandomLongitude()));
    }

    // TODO ADD K MEANS
}

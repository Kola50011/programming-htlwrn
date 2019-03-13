#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include "coordinate.h"
#include "person.h"
#include "dbmanager.h"
#include "center.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent, int port) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    s{this, port}
{
    ui->setupUi(this);
    s.set_dbm(&DbManager::getInstance());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void setClosestCenter(vector<Center> &centers, Person &person)
{
    double distance = INT32_MAX;
    Center *toAdd;
    for (Center &center : centers)
    {
        center.removePerson(person);
        auto distanceToCenter = person.getDistance(center.latitude, center.longitude);
        if (distance > distanceToCenter)
        {
            toAdd = &center;
            distance = distanceToCenter;
        }
    }

    toAdd->addPerson(person);
}

vector<Person> calculateRoute(Center &center)
{
    vector<QString> visited;
    vector<Person> res;

    res.push_back(center.people[0]);
    visited.push_back(center.people[0].name);
    while (res.size() != center.people.size())
    {
        double distance = INT32_MAX;
        Person *toAdd;
        Person last = res[res.size() - 1];
        for (Person &person : center.people)
        {
            if (find(visited.begin(), visited.end(), person.name) == visited.end())
            {
                auto distanceToLast = person.getDistance(last.latitude, last.longitude);
                if (distance > distanceToLast)
                {
                    distance = distanceToLast;
                    toAdd = &person;
                }
            }
        }
        res.push_back(*toAdd);
        visited.push_back(toAdd->name);
    }
    return res;
}

void MainWindow::on_clusterButton_clicked()
{
    if (ui->amountEdit->text().isEmpty()) {
        return;
    }

    DbManager database = DbManager::getInstance();
    vector<Person> people = database.people;
    vector<Center> centers;

    for (int i{1}; i <= ui->amountEdit->text().toInt(); i++)
    {
        centers.push_back(Center(database.getRandomLatitude(), database.getRandomLongitude()));
    }

    bool centerChanged = true;
    while (centerChanged)
    {
        centerChanged = false;
        for (Person &person : people)
        {
            setClosestCenter(centers, person);
        }
        for (Center &center : centers)
        {
            if (center.adjustCenter() == true)
            {
                centerChanged = true;
            }
        }
    }

    // Draw
    ui->widget->resetPic();
    for (Center &center : centers)
    {
        int r1 = rand()%(255-0 + 1) + 0;
        int r2 = rand()%(255-0 + 1) + 0;
        int r3 = rand()%(255-0 + 1) + 0;
        auto people = calculateRoute(center);
        ui->widget->drawPeople(people, QColor(r1, r2, r3));
        ui->widget->drawCenter(center, QColor(r1, r2, r3));
    }
}

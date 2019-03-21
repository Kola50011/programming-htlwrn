#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include "coordinate.h"
#include "person.h"
#include "dbmanager.h"
#include "center.h"
#include <thread>
#include <QRect>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, int port) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    s{this, port}
{
    ui->setupUi(this);
    s.set_dbm(&DbManager::getInstance());
    connect(ui->widget, &DrawableMapWidget::clicked, this, &MainWindow::dmw_clicked);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::slider_moved);
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
    DbManager database = DbManager::getInstance();
    vector<Person> people = database.people;
    vector<Center> centers;

    if (people.size() < ui->horizontalSlider->value()) {
        QMessageBox mb;
        mb.setText("You can't have more clusters than people!");
        mb.exec();
        return;
    }

    for (int i{1}; i <= ui->horizontalSlider->value(); i++)
    {
        int r1 = rand()%(255-0 + 1) + 0;
        int r2 = rand()%(255-0 + 1) + 0;
        int r3 = rand()%(255-0 + 1) + 0;
        centers.push_back(Center(database.getRandomLatitude(), database.getRandomLongitude(), QColor(r1, r2, r3)));
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
        ui->widget->drawPeople(center.people, center.col);
    }
    center_objs = centers;
}

void MainWindow::dmw_clicked(int x, int y)
{
    QPoint clicked(x, y);
    for (Center& c : center_objs) {
        QRect bb = c.get_bounding_box();
        if (bb.contains(clicked)) {
            auto people = calculateRoute(c);
            ui->widget->connectPeople(people, c.col);
        }
    }
}

void MainWindow::slider_moved(int value)
{
    ui->amountLabel->setText((std::string{"Clusters: "} + std::to_string(value)).c_str());
}

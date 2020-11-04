/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#ifndef CLIENT_CONN_H
#define CLIENT_CONN_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QString>

#include "dbmanager.h"


class client_conn : public QThread
{
    Q_OBJECT

public:
    client_conn(int desc, QObject* parent = nullptr) :
            socket_desc{desc} {};

    // QThread interface
protected:
    virtual void run();

public slots:
    void on_disconnected();
    void on_ready_read();

signals:
    void new_person_added(Person p);

private:
    int socket_desc;
    QTcpSocket* sock;
    DbManager* dbm;
};

#endif // CLIENT_CONN_H

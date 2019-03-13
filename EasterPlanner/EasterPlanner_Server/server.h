#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "dbmanager.h"
#include <QMetaType>

class server : public QTcpServer
{
    Q_OBJECT

public:
    server(QObject* parent = nullptr, int port = 6969);
    void set_dbm(DbManager* _dbm) {
        dbm = _dbm;
    }

public slots:
    void on_new_person(Person p);

    // QTcpServer interface
protected:
    virtual void incomingConnection(qintptr handle);

private:
    DbManager* dbm;
};

#endif // SERVER_H

#include "server.h"

#include "client_conn.h"

server::server(QObject* parent, int port) :
    QTcpServer{parent}
{
    qRegisterMetaType<Person>();
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Could not start server";
    }
}

void server::on_new_person(Person p)
{
    dbm->addPerson(p);
}

void server::incomingConnection(qintptr handle)
{
    client_conn* con = new client_conn(handle, this);

    connect(con, SIGNAL(finished()), con, SLOT(deleteLater()));
    connect(con, &client_conn::new_person_added, this, &server::on_new_person);

    con->start();
}


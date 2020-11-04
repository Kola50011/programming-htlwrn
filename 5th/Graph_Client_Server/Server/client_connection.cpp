#include "client_connection.h"

client_connection::client_connection(QTcpSocket* _sock) : sock{_sock}
{
    connect(sock, &QTcpSocket::readyRead, this, &client_connection::on_ready_read);
}

client_connection::~client_connection()
{
    sock->close();
}

void client_connection::on_ready_read()
{
    QString xml = sock->readAll();
    qDebug() << xml;

    emit route_received(xml);

}

void client_connection::on_route_calculated(QString route)
{
    qDebug() << route;
    sock->write(route.toStdString().data());
    sock->flush();
}

void client_connection::run()
{
    this->exec();
}

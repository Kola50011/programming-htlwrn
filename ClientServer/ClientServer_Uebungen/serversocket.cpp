#include "serversocket.h"

void ServerSocket::on_data_received()
{
    qDebug() << "Got Data!";
    emit sql_from_client_received(socket->readAll());
}

void ServerSocket::sql_reply_receiver(QString repl)
{
    qDebug() << repl;
    socket->write(repl.toStdString().data());
    socket->flush();
}

ServerSocket::ServerSocket(QTcpSocket *_sock) : socket{_sock}
{
    connect(socket, &QTcpSocket::readyRead, this, &ServerSocket::on_data_received);
}

void ServerSocket::run()
{
    this->exec();
}


#include "serversocket.h"

#include <QDomDocument>
#include <QDomElement>

void ServerSocket::on_data_received()
{
    qDebug() << "Got Data!";
    emit sql_from_client_received(socket->readAll());
}

void ServerSocket::sql_reply_receiver(QString repl)
{
    qDebug() << repl;

    QDomDocument doc;
    QDomElement elem = doc.createElement("reply");
    doc.appendChild(elem);
    elem.appendChild(doc.createTextNode(repl));

    socket->write(doc.toString().toStdString().data());
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


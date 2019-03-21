/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#include "client_conn.h"

#include <QJsonObject>
#include <QJsonDocument>

void client_conn::run()
{
    qDebug() << "Thread started";
    sock = new QTcpSocket();

    if(!sock->setSocketDescriptor(socket_desc)) {
     return;
    }

    connect(sock, SIGNAL(readyRead()), this, SLOT(on_ready_read()), Qt::DirectConnection);
    connect(sock, SIGNAL(disconnected()), this, SLOT(on_disconnected()), Qt::DirectConnection);

    qDebug() << sock << " Client connected";

    exec();
}

void client_conn::on_disconnected()
{
    sock->deleteLater();
    exit(0);
}

void client_conn::on_ready_read()
{
    qDebug() << "Ready to read!";
    QJsonObject inp = QJsonDocument::fromJson(sock->readAll()).object();
    qDebug() << inp;

    emit new_person_added(Person(inp["name"].toString(), inp["lat"].toDouble(), inp["lon"].toDouble()));
}

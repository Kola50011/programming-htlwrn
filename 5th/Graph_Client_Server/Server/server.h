#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "client_connection.h"
#include "graph.h"

class server : public QObject
{
    Q_OBJECT

public:
    server(quint16 port);
    virtual ~server() = default;

private slots:
    void on_incomming_connection();
    void on_route_received(QString xml);

signals:
    void route_calculated(QString route);

private:
    QTcpServer* tcp_server;
    Graph* graph = new Graph{};
};

#endif // SERVER_H

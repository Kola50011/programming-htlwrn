#include "server.h"

server::server(quint16 port)
{
    tcp_server = new QTcpServer{};
    tcp_server->listen(QHostAddress::Any, port);
    connect(tcp_server, &QTcpServer::newConnection, this, &server::on_incomming_connection);

    graph->get_route_breadth_first_search("Wien", "Bregenz");
}

//server::~server()
//{
//    tcp_server->close();
//}

void server::on_incomming_connection()
{

    QTcpSocket* sock = tcp_server->nextPendingConnection();
    client_connection* conn = new client_connection{sock};

    connect(conn, &client_connection::route_received, this, &server::on_route_received);
    connect(this, &server::route_calculated, conn, &client_connection::on_route_calculated);

    conn->start();

}

void server::on_route_received(QString xml)
{
    QXmlStreamReader xml_reader{xml};
    QVector<QString> route;

    while (xml_reader.readNextStartElement()) {
        if (xml_reader.name() == "stop") {
            route.push_back(xml_reader.readElementText());
        }
    }

    if (route.size() < 2) {
        emit route_calculated("Please specify at least 2 Stops!");
        return;
    }

    qDebug() << "Calculating Route!";
    std::vector<Node*> vctr = graph->get_route(route[0].toStdString(), route[1].toStdString());
    graph->get_route_breadth_first_search(route[0].toStdString(), route[1].toStdString());

    qDebug() << "Calculated Route!";
    QString msg{};
    if (vctr.size() != 0) {

        msg.append(vctr[0]->name.data());
        for (size_t i{1}; i < vctr.size(); i++) {
            msg.append((" -> " + vctr[i]->name).data());
        }
        msg.prepend("Route: ");


    } else {
        msg = "No route found!";
    }

    emit route_calculated(msg);
}

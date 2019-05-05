#include "server.h"

server::server(quint16 port)
{
    tcp_server = new QTcpServer{};
    tcp_server->listen(QHostAddress::Any, port);
    connect(tcp_server, &QTcpServer::newConnection, this, &server::on_incomming_connection);
}

//server::~server()
//{
//    tcp_server->close();
//}

void server::on_incomming_connection()
{

    QTcpSocket* sock = tcp_server->nextPendingConnection();
    client_connection* conn = new client_connection{sock};

    connect(conn, &client_connection::route_received, this, &server::on_route_received, Qt::DirectConnection);
    //connect(this, &server::route_calculated, conn, &client_connection::on_route_calculated, Qt::DirectConnection);

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
    auto bws = graph->get_route_breadth_first_search(route[0].toStdString(), route[1].toStdString());
    qDebug() << "Calculated Route!";

    QString xml_output;
    QXmlStreamWriter xml_w{&xml_output};

    xml_w.writeStartDocument();
    xml_w.writeStartElement("routes");
    xml_w.writeStartElement("fastest_route");
    for (Node* node : vctr) {
        xml_w.writeTextElement("stop", node->name.data());
    }
    xml_w.writeEndElement();

    for (auto& route : bws) {
        xml_w.writeStartElement("route");
        for (Node* stop : route) {
            xml_w.writeTextElement("stop", stop->name.data());
        }
        xml_w.writeEndElement();
    }
    xml_w.writeEndElement();
    xml_w.writeEndDocument();


    reinterpret_cast<client_connection*>(sender())->on_route_calculated(xml_output);
}

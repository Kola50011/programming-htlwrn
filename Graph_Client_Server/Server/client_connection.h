#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QtXml>

class client_connection : public QThread
{
    Q_OBJECT

public:
    client_connection(QTcpSocket* _sock);
    virtual ~client_connection();

private slots:
    void on_ready_read();

public slots:
    void on_route_calculated(QString route);

private:
    QTcpSocket* sock;

signals:
    void route_received(QString route);

    // QThread interface
protected:
    virtual void run() override;
};

#endif // CLIENT_CONNECTION_H

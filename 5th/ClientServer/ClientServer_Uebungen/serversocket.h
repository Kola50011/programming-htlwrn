#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QThread>
#include <QTcpSocket>

class ServerSocket : public QThread
{
    Q_OBJECT
private:
    QTcpSocket* socket;

private slots:
    void on_data_received();

public slots:
    void sql_reply_receiver(QString repl);

signals:
    void sql_from_client_received(QString sql);

public:
    ServerSocket(QTcpSocket* _sock);

    // QThread interface
protected:
    virtual void run() override;
};

#endif // SERVERSOCKET_H

#ifndef SERVER_PORT_H
#define SERVER_PORT_H

#include <QDialog>

#include "ui_server_port.h"

namespace Ui {
class server_port;
}

class server_port : public QDialog
{
    Q_OBJECT

public:
    explicit server_port(QString& host, QString& port, QWidget *parent = nullptr);
    ~server_port();


private slots:

private:
    Ui::server_port *ui;
};

#endif // SERVER_PORT_H

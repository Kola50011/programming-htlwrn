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
    explicit server_port(QWidget *parent = nullptr);
    ~server_port();
    int get_port() {
        return ui->portLineEdit->text().toInt();
    }
    QString get_host() {
        return ui->serverLineEdit->text();
    }

private slots:

private:
    Ui::server_port *ui;
};

#endif // SERVER_PORT_H

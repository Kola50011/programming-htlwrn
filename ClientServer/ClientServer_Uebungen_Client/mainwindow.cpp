#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QDebug>
#include <QtXml>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendBtn_clicked()
{

    if (!connected) {
        sock = new QTcpSocket();
        sock->connectToHost(ui->hostInput->text(), ui->portInput->text().toInt());
        if (sock->waitForConnected()) {
            qDebug() << "Successfully connected!";
            connected = true;
            connect(sock, &QTcpSocket::readyRead, this, &MainWindow::on_data_received);
        } else {
            qDebug() << "Failed!";
        }
    }
    QJsonObject toSend;
    toSend["input"] = ui->sqlInput->text();
    QJsonDocument document = QJsonDocument{toSend};

    // QString xml_str;
    // QXmlStreamWriter xml_writer{&xml_str};
    // xml_writer.writeStartDocument();
    // xml_writer.writeTextElement("query", ui->sqlInput->text());
    // xml_writer.writeEndDocument();

    // qDebug() << xml_str;

    // sock->write(xml_str.toStdString().data());
    sock->write(document.toJson());
}


void MainWindow::on_data_received()
{
    QJsonDocument document = QJsonDocument::fromJson(sock->readAll());
    QJsonObject jsonObject = document.object();
    QString repl = jsonObject["input"].toString();

    qDebug() << repl;
    ui->messages->append(repl);

    // QString repl = sock->readAll().toStdString().data();
    // QXmlStreamReader reader{repl};
    // while (reader.readNextStartElement()) {
    //     if (reader.name() == "reply") {
    //         ui->messages->append(reader.readElementText());
    //     }
    // }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sock = new QTcpSocket{this};
    if (!sock->isValid()) {
        sock->connectToHost("localhost", 6969);
        if (sock->waitForConnected()) {
            qDebug() << "Connected to local Server!";
            connect(sock, &QTcpSocket::readyRead, this, &MainWindow::on_ready_read);
        } else {
            qDebug() << "Could not connect to server!";
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox mb;
    mb.setText("Created by Königsreiter Simon & Lampalzer Konstantin");
    mb.exec();
}

void MainWindow::on_ready_read()
{
    QString text{"Cheapest Route: \n"};
    ui->label->setText(text);
    QString msg = sock->readAll();
    QXmlStreamReader* xml = new QXmlStreamReader{msg};
    while (!xml->atEnd()) {
        xml->readNext();
        if (xml->name() == "fastest_route") {
            while (xml->readNextStartElement()) {
                //qDebug() << xml->name();
                text.append(xml->readElementText());
                text.append(" -> ");
            }
            text.chop(4);
            text.append("\nAdditional Routes:\n");
        } else if (xml->name() == "route") {
            while (xml->readNextStartElement()) {
                //qDebug() << xml->name();
                text.append(xml->readElementText());
                text.append(" -> ");
            }
            text.chop(4);
            text.append("\n");
        }
    }
    ui->label->setText(text);
}

void MainWindow::on_pushButton_clicked()
{
    if (!sock->isValid()) {
        sock->connectToHost("localhost", 6969);
        if (sock->waitForConnected()) {
            qDebug() << "Connected to local Server!";
            connect(sock, &QTcpSocket::readyRead, this, &MainWindow::on_ready_read);
        } else {
            qDebug() << "Could not connect to server!";
        }
    }

    QStringList route = ui->planRoute->text().simplified().trimmed().split(";", QString::SkipEmptyParts);

    QString xml_outp;
    QXmlStreamWriter xml_writer{&xml_outp};

    xml_writer.writeStartDocument();
    xml_writer.writeStartElement("route");

    for (QString& stop : route) {
        xml_writer.writeTextElement("stop", stop.trimmed().simplified());
    }

    xml_writer.writeEndElement();
    xml_writer.writeEndDocument();

    qDebug() << xml_outp;
    sock->write(xml_outp.toStdString().data());
    sock->flush();

}

#include <QCoreApplication>

#include "server.h"

#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Starting Server on port" << 6969 << "!";
    server s{6969};

    return a.exec();
}

/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */


#include "mainwindow.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Port for the ultimate EasterPlanner");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOptions({
                         {{"p", "port"}, "Port to listen on", "port", "6969"}
                     });
    parser.parse(a.arguments());

    MainWindow w{nullptr, parser.value("port").toInt()};
    w.show();

    return a.exec();
}

/*************************************************************************
 * Name = Konstantin Lampalzer
 * Class = 5BHIF
 * Date = 14.12.18
*************************************************************************/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.load();

    return a.exec();
}

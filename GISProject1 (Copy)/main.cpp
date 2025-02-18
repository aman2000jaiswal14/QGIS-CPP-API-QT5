#include "mainwindow.h"

#include <QApplication>
#include <qgsapplication.h>
int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    QgsApplication qgisapp(argc,argv,true);
    qgisapp.setPrefixPath("/usr/local");
    qgisapp.init();
    qDebug()<<"App Started...";
    MainWindow w;
    w.show();
    return a.exec();
}

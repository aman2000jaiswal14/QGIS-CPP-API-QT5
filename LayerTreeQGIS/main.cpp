#include "mainwindow.h"

#include <QApplication>
#include <qgsapplication.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    QgsApplication::setPrefixPath("/usr/local",true);
    QgsApplication app(argc, argv, true);
    QgsApplication::init();
    qDebug()<<"App Started...";
    MainWindow w;
    w.show();
    int returnval  = a.exec();
    QgsApplication::exitQgis();
    return returnval;
}

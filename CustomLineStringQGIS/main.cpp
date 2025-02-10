#include "mainwindow.h"

#include <QApplication>
#include <qgsapplication.h>
int main(int argc, char *argv[])
{

    QgsApplication qgisapp(argc,argv,true);
    qgisapp.setPrefixPath("/usr/local");
    qgisapp.init();
    MainWindow w;
    w.show();
    return qgisapp.exec();
}

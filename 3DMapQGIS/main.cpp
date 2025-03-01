#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QgsApplication qgsApp(argc, argv, true);

    QgsApplication::setPrefixPath("/usr/local", true); // Replace with your QGIS install path
    QgsApplication::initQgis();
    MainWindow w;
    w.show();
    return a.exec();
}

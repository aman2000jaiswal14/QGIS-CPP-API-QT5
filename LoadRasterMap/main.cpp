#include "mainwindow.h"

#include <QApplication>
#include "qgsapplication.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the QGIS application
    QgsApplication app(argc, argv, true);

    MainWindow w;
    w.show();

    return app.exec();
}

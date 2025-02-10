#include "mainwindow.h"

#include <QApplication>
#include <qgsapplication.h>
int main(int argc, char *argv[])
{
    QgsApplication a(argc, argv,true);
    QgsApplication::setPrefixPath("/usr/local");
    MainWindow w;
    w.show();
    return a.exec();
}

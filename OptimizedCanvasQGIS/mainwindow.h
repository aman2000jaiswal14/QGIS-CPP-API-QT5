#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgsmapcanvas.h"
#include "qgsrasterlayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaprenderercache.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QgsMapCanvas *canvas;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

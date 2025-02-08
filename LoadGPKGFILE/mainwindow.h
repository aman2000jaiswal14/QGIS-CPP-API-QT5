#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "qgsvectorlayer.h"
#include "qgsmapcanvas.h"
#include "qgslayertreeview.h"
#include "qgslayertree.h"
#include "qgsrasterlayer.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QgsLayerTree* layerTree;
    QgsMapCanvas* canvas;
};
#endif // MAINWINDOW_H

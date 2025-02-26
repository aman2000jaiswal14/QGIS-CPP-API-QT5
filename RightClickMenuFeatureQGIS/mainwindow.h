#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custommapcanvas.h"
#include "qgsmapcanvas.h"
#include "qgsmaplayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaptool.h"
#include "qgsfeature.h"
#include "qgsmaptoolidentify.h"

#include "qgspointxy.h"
#include "qgsgeometry.h"
#include "qgssinglesymbolrenderer.h"
#include "custommarkersymbol.h"
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

private :
    CustomMapCanvas *canvas;
    QgsVectorLayer *vectorLayer;
    QgsVectorLayer *circleLayer;
    QgsFeature feature,feature2,feature3;
    CustomMarkerSymbol *customSymbol;

};
#endif // MAINWINDOW_H

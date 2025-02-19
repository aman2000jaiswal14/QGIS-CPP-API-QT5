#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgsmapcanvas.h"
#include "qgsvectorlayer.h"
#include "qgsrasterlayer.h"
#include "qgssymbol.h"
#include "qgsmarkersymbol.h"
#include "qgsmarkersymbollayer.h"
#include <QObject>
#include <QLabel>
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
    QgsMapCanvas *canvas;
    CustomMarkerSymbol *customSymbol;
    QgsVectorLayer* vectorLayer;
    QgsFeature feature;
    QgsFeature feature2;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

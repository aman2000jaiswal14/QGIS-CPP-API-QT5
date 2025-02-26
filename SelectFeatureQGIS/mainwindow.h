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
#include "qgsmaptoolidentifyfeature.h"
#include "qgsmaptoolidentify.h"
#include "qgscircle.h"
#include "qgspoint.h"
#include "qgspolygon.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QgsMapCanvas *canvas;
    QgsMarkerSymbol *customSymbol;
    QgsVectorLayer* vectorLayer;
    QgsVectorLayer* circleLayer;
    QgsFeature feature;
    QgsFeature feature2;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    void removeAllFeatures(QgsVectorLayer* layer);

public slots:
    void featureIdentifiedSlot(const QgsFeature &feature);
    void drawCircleAroundSelectedFeature( const QgsFeatureIds &selected, const QgsFeatureIds &deselected, bool clearAndSelect );
};
#endif // MAINWINDOW_H

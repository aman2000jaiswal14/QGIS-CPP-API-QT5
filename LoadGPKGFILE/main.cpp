#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "qgsvectorlayer.h"
#include "qgsmapcanvas.h"
#include "qgslayertreeview.h"
#include "qgslayertree.h"
#include "qgsrasterlayer.h"

#include <qgsapplication.h>


#include "qgsapplication.h"
int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);

    QgsApplication::setPrefixPath("/usr/local", true);
    // Initialize the QGIS application
    QgsApplication app(argc, argv, true);
    // Initialize QGIS application
    app.init();
    MainWindow w;
    w.show();

    return app.exec();
}
/*
int main(int argc, char *argv[])
{

    QgsApplication::setPrefixPath("/usr/local", true); // Path to your QGIS installation
    QgsApplication app(argc, argv, true); // True means no GUI

    // Initialize QGIS application
    app.init();

    // Create a map canvas to display the map
    QgsMapCanvas* canvas = new QgsMapCanvas();
    canvas->setCanvasColor(Qt::white);

    // Create a QGraphicsView and scene for visualization
    QGraphicsView* view = new QGraphicsView();
    QGraphicsScene* scene = new QGraphicsScene(view);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->resize(800, 600);
    view->show();


    // Load the world_map.gpkg as a vector layer
    QgsVectorLayer* layer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");

    if (!layer->isValid()) {
        qDebug() << "Layer failed to load!";
        return -1;
    }

    // Add layer to the map canvas
    QgsLayerTree* layerTree = new QgsLayerTree();
    layerTree->addLayer(layer);
    canvas->setLayers({ layer });


    // Set extent of the map to the layer's extent
    canvas->setExtent(layer->extent());

    // Show map on the canvas
    canvas->show();
    return app.exec();
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
*/

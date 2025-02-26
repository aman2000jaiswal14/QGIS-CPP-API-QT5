#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Use the custom map canvas
    canvas = new CustomMapCanvas(this);

    // Load layers and set up the canvas (as in your original code)
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");
    circleLayer = new QgsVectorLayer("Polygon?crs=EPSG:4326", "Circle Layer", "memory");

    // Add layers to the canvas
    canvas->setLayers({circleLayer, vectorLayer, mapLayer});
    canvas->setExtent(mapLayer->extent());

    // Add the canvas to the UI
    ui->verticalLayout->addWidget(canvas);


    //Setting symbol
    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(vectorLayer->renderer());

    customSymbol = new CustomMarkerSymbol;

    QgsSymbol* symbol = renderer->symbol();
    symbol->changeSymbolLayer(0,customSymbol);

    // Create a point geometry
    QgsGeometry pointGeometry = QgsGeometry::fromPointXY(QgsPointXY(64, 32));

    // Create a feature and add it to the vector layer
    feature.initAttributes(2);
    feature.setFields(vectorLayer->fields());
    feature.setAttribute("id", 1);
    feature.setAttribute("angle", 30);
    feature.setGeometry(pointGeometry);
    vectorLayer->dataProvider()->addFeature(feature);


    // Create a point geometry
    QgsGeometry pointGeometry2 = QgsGeometry::fromPointXY(QgsPointXY(20, 16));

    // Create a feature and add it to the vector layer
    feature2.initAttributes(2);
    feature2.setFields(vectorLayer->fields());
    feature2.setAttribute("id", 2);
    feature2.setAttribute("angle", 120);
    feature2.setGeometry(pointGeometry2);
    vectorLayer->dataProvider()->addFeature(feature2);


    // Create a point geometry
    QgsGeometry pointGeometry3 = QgsGeometry::fromPointXY(QgsPointXY(20, 16));

    // Create a feature and add it to the vector layer
    feature3.initAttributes(2);
    feature3.setFields(vectorLayer->fields());
    feature3.setAttribute("id", 3);
    feature3.setAttribute("angle", 100);
    feature3.setGeometry(pointGeometry3);
    vectorLayer->dataProvider()->addFeature(feature3);



    vectorLayer->triggerRepaint();

}

MainWindow::~MainWindow() {
    delete ui;
}

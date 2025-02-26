#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "qgssinglebandgrayrenderer.h"
#include "qgsfillsymbollayer.h"
#include "qgsfillsymbol.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create the map canvas
    canvas = new QgsMapCanvas(this);
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    // Create a vector layer for points
    vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");
    circleLayer = new QgsVectorLayer("Polygon?crs=EPSG:4326", "Circle Layer", "memory");

    // Style the circle layer
    QgsSimpleFillSymbolLayer* fillSymbolLayer = new QgsSimpleFillSymbolLayer();
    fillSymbolLayer->setColor(QColor(255, 0, 0, 100)); // Red with transparency
    fillSymbolLayer->setStrokeColor(QColor(255, 0, 0)); // Red border
    fillSymbolLayer->setStrokeWidth(1);

    QgsFillSymbol* fillSymbol = new QgsFillSymbol();
    fillSymbol->changeSymbolLayer(0, fillSymbolLayer);

    QgsSingleSymbolRenderer* renderer = new QgsSingleSymbolRenderer(fillSymbol);
    circleLayer->setRenderer(renderer);

    // Add the circle layer to the project
    QgsProject::instance()->addMapLayer(circleLayer);

    // Connect the selection change signal
    connect(vectorLayer, &QgsVectorLayer::selectionChanged, this, &MainWindow::drawCircleAroundSelectedFeature);
    // Add fields to the layer if needed (for attributes)
    QgsFields fields;
    fields.append(QgsField("id", QVariant::Int));
    fields.append(QgsField("angle", QVariant::Double));

    // Convert QgsFields to QList<QgsField>
    QList<QgsField> fieldList = fields.toList();

    // Add fields to the vector layer's data provider
    vectorLayer->dataProvider()->addAttributes(fieldList);

    // Update the layer fields
    vectorLayer->updateFields();

    // Load a base map layer


    // Set the CRS of the vector layer to match the map layer
    vectorLayer->setCrs(mapLayer->crs());
    circleLayer->setCrs(mapLayer->crs());
    // Set the layers on the canvas
    canvas->setLayers({circleLayer,vectorLayer, mapLayer});
    canvas->setExtent(mapLayer->extent());

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
    vectorLayer->triggerRepaint();


    // Set the canvas as the central widget
    // setCentralWidget(canvas);
    ui->verticalLayout->addWidget(canvas);


    vectorLayer->triggerRepaint();






    // feature selection

    QgsMapToolIdentifyFeature* identifyTool = new QgsMapToolIdentifyFeature(canvas);
    identifyTool->setLayer(vectorLayer);

    // Set the tool to the canvas
    canvas->setMapTool(identifyTool);

// Connect the tool's signal to a slot to handle the selection
    connect(identifyTool, SIGNAL(featureIdentified(const QgsFeature&)), this, SLOT(featureIdentifiedSlot(const QgsFeature&)));

    //--

    canvas->setSelectionColor(QColor(255, 0, 0, 127)); // Red with 50% transparency



    // Create a label to display the latitude and longitude
    QLabel* coordinatesLabel = new QLabel(this);
    coordinatesLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    coordinatesLabel->setStyleSheet("color: black; background-color: rgba(255, 255, 255, 200); padding: 5px;");
    coordinatesLabel->setFixedWidth(200);
    coordinatesLabel->setFixedHeight(30);
    coordinatesLabel->move(10, height() - 40); // Position it in the bottom left
    coordinatesLabel->show();

    // Connect the canvas mouseMoveEvent to a slot to display coordinates
    connect(canvas, &QgsMapCanvas::xyCoordinates, this, [=](QgsPointXY coordinates) {
        // Convert the coordinates to lat/lon (EPSG:4326)
        QgsCoordinateReferenceSystem crs = mapLayer->crs();
        QgsCoordinateTransform transform(crs, QgsCoordinateReferenceSystem("EPSG:4326"), QgsProject::instance());

        QgsPointXY lonLat = transform.transform(coordinates);
        double latitude = lonLat.y();
        double longitude = lonLat.x();

        // Update the label with the coordinates
        coordinatesLabel->setText(QString("Lat: %1, Lon: %2").arg(latitude).arg(longitude));
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::featureIdentifiedSlot(const QgsFeature &feature)
{
    vectorLayer->selectByIds(QgsFeatureIds() << feature.id());
    qDebug()<<"selected feature : "<<feature.id();
    canvas->zoomToSelected(vectorLayer);
    canvas->refresh();

}


void MainWindow::drawCircleAroundSelectedFeature( const QgsFeatureIds &selected, const QgsFeatureIds &deselected, bool clearAndSelect ) {
    removeAllFeatures(circleLayer);
    for (QgsFeatureId id: selected)
    {
        QgsFeature feature = vectorLayer->getFeature(id);
        qDebug()<<"selected : "<<id;
        QgsGeometry selectedGeometry = feature.geometry();

        // Create a circular buffer (radius in map units, for example, 0.1 units)
        double bufferRadius = 5;  // Adjust the radius as needed
        QgsGeometry bufferGeometry = selectedGeometry.buffer(bufferRadius, 10);  // 10 segments for smoothness

        // Create a new feature for the buffer geometry
        QgsFeature bufferFeature;
        bufferFeature.setId(feature.id());
        bufferFeature.setGeometry(bufferGeometry);

        // Add the buffer feature to the circle layer
        circleLayer->dataProvider()->addFeature(bufferFeature);

        // Refresh the layer and canvas to display the circle

    }

    qDebug()<<"cicle feature count : "<<circleLayer->featureCount();
    circleLayer->triggerRepaint();

}
void MainWindow::removeAllFeatures(QgsVectorLayer* layer) {
    if (!layer || !layer->isValid()) {
        qWarning() << "Layer is not valid!";
        return;
    }

    // Get all feature IDs in the layer
    QgsFeatureIds featureIds = layer->allFeatureIds();

    // Delete all features
    if (!featureIds.isEmpty()) {
        layer->dataProvider()->deleteFeatures(featureIds);
        layer->triggerRepaint(); // Refresh the layer to reflect the changes
    }
}

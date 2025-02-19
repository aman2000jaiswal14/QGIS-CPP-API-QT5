#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the map canvas
    canvas = new QgsMapCanvas(this);

    // Create a vector layer for points
    vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");


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
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");

    // Set the CRS of the vector layer to match the map layer
    vectorLayer->setCrs(mapLayer->crs());

    // Set the layers on the canvas
    canvas->setLayers({vectorLayer, mapLayer});
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


    //Setting symbol
    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(vectorLayer->renderer());

    customSymbol = new CustomMarkerSymbol;

    QgsSymbol* symbol = renderer->symbol();
    symbol->changeSymbolLayer(0,customSymbol);


    vectorLayer->triggerRepaint();





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

void MainWindow::on_pushButton_clicked()
{
    QgsFeatureIterator it = vectorLayer->getFeatures(QgsFeatureRequest().setFilterFid(1));
    QgsFeature feature;
    if (it.nextFeature(feature))
    {
        // Get the current angle
        double currentAngle = feature.attribute("angle").toDouble();

        // Rotate the angle by 90 degrees
        double newAngle = currentAngle + 45;

        // Update the feature's angle attribute
        vectorLayer->startEditing();
        feature.setAttribute("angle", newAngle);
        vectorLayer->updateFeature(feature);
        vectorLayer->commitChanges();

        // Trigger a repaint to update the display
        vectorLayer->triggerRepaint();
    }
}


void MainWindow::on_pushButton_2_clicked()
{

    // Get the feature with id 2
    QgsFeatureIterator it = vectorLayer->getFeatures(QgsFeatureRequest().setFilterFid(2));
    QgsFeature feature;
    if (it.nextFeature(feature))
    {
        double currentAngle = feature.attribute("angle").toDouble();

        // Rotate the angle by 90 degrees
        double newAngle = currentAngle + 45;
        // Update the feature's angle attribute to 275 degrees
        vectorLayer->startEditing();
        feature.setAttribute("angle", newAngle);
        vectorLayer->updateFeature(feature);
        vectorLayer->commitChanges();

        // Trigger a repaint to update the display
        vectorLayer->triggerRepaint();
    }

}


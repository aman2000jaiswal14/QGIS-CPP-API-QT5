#include "custommapcanvas.h"
#include <QLabel>
CustomMapCanvas::CustomMapCanvas() {
    // this->setCanvasColor(Qt::green);

    // Create a vector layer
    QgsVectorLayer* vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    vectorLayer->setCrs(mapLayer->crs());
    // Add fields to the layer if needed (for attributes)
    QgsField field("name", QVariant::String);
    vectorLayer->dataProvider()->addAttributes({field});
    vectorLayer->updateFields();

    // Initialize the canvas and set up the tool

    this->setExtent(QgsRectangle(-180, -90, 180, 90)); // Set extent to world bounds
    this->setLayers({vectorLayer,mapLayer});

    // Create and set the drawing tool
    DrawPointTool* drawTool = new DrawPointTool(this);
    drawTool->setLayer(vectorLayer);
    this->setMapTool(drawTool);
    qDebug()<<"maptool set";



    // Create a label to display the latitude and longitude
    QLabel* coordinatesLabel = new QLabel(this);
    coordinatesLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    coordinatesLabel->setStyleSheet("color: black; background-color: rgba(255, 255, 255, 200); padding: 5px;");
    coordinatesLabel->setFixedWidth(200);
    coordinatesLabel->setFixedHeight(30);
    coordinatesLabel->move(10, height() - 40); // Position it in the bottom left
    coordinatesLabel->show();

    // Connect the canvas mouseMoveEvent to a slot to display coordinates
    connect(this, &QgsMapCanvas::xyCoordinates, this, [=](QgsPointXY coordinates) {
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

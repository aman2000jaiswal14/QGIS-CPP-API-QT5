#include "custommapcanvas.h"
#include <QLabel>
#include "qgsproviderregistry.h"

CustomMapCanvas::CustomMapCanvas() {
    // Create a vector layer

    QgsVectorLayer* vectorLayer = new QgsVectorLayer("Polygon?crs=EPSG:4326", "PolygonsLayer", "memory");
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    QgsVectorLayer *mapLayer2 = new QgsVectorLayer("/home/aman/map1/Layer2.gpkg","Layer2","ogr");
    QgsVectorLayer *mapLayer3 = new QgsVectorLayer("/home/aman/dev/cpp/QGIS/tests/testdata/projects/bad_layers_test.gpkg","bad_layer","ogr");
    QgsRasterLayer *rasterLayer1 = new QgsRasterLayer("/home/aman/dev/cpp/QGIS/tests/testdata/projects/bad_layer_raster_test.tiff","raster1");

    vectorLayer->setCrs(mapLayer->crs());
    mapLayer2->setCrs(mapLayer->crs());
    mapLayer3->setCrs(mapLayer->crs());
    rasterLayer1->setCrs(mapLayer->crs());



    // Add fields to the layer if needed (for attributes)
    QgsField field("name", QVariant::String);
    vectorLayer->dataProvider()->addAttributes({field});
    vectorLayer->updateFields();

    // Initialize the canvas and set up the tool
    this->setExtent(QgsRectangle(-180, -90, 180, 90)); // Set extent to world bounds
    this->setLayers({vectorLayer,mapLayer3,rasterLayer1,mapLayer2});

    // Create and set the drawing tool
    DrawPolygonTool* drawTool = new DrawPolygonTool(this);
    drawTool->setLayer(vectorLayer);
    this->setMapTool(drawTool);

    qDebug() << "Polygon drawing tool set";

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

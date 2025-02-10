#include "custommapcanvas.h"
#include <QLabel>
CustomMapCanvas::CustomMapCanvas() {
    // this->setCanvasColor(Qt::green);

    // Create a vector layer
    QgsVectorLayer* vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    vectorLayer->setCrs(mapLayer->crs());


    // Add fields to the layer if needed (for attributes)
    QgsFields fields;
    fields.append(QgsField("id", QVariant::Int));      // Define 'id' field with integer type
    fields.append(QgsField("name", QVariant::String)); // Define 'name' field with string type

    // Convert QgsFields to QList<QgsField>
    QList<QgsField> fieldList = fields.toList();

    // Add fields to the vector layer's data provider
    vectorLayer->dataProvider()->addAttributes(fieldList);

    // Update the layer fields
    vectorLayer->updateFields();

    // Check the number of fields
    qDebug() << "Number of fields in vector layer:" << vectorLayer->fields().size();
    qDebug() << "Fields in vector layer:" << vectorLayer->fields();
    for (int i = 0; i < vectorLayer->fields().size(); ++i)
    {
        qDebug() << "Field" << i << ":" << vectorLayer->fields().at(i).name();
    }


    // --- Labeling Setup ---
    // Create label settings
    QgsPalLayerSettings labelSettings;

    // Set the field to be used for labels
    labelSettings.fieldName = "id";  // Use the "name" field for labeling



    QgsTextFormat textFormat;
    textFormat.setSize(10);  // Set font size
    textFormat.setColor(QColor(0, 0, 0));  // Set font color to black
    labelSettings.setFormat(textFormat);


    // Create labeling object for the vector layer
    QgsVectorLayerSimpleLabeling *simpleLabeling = new QgsVectorLayerSimpleLabeling(labelSettings);

    // Set label properties (optional, customize as needed)


    // Enable labeling for the vector layer
    vectorLayer->setLabeling(simpleLabeling);

    // Refresh the layer to display the label
    vectorLayer->setLabelsEnabled(true);
    vectorLayer->triggerRepaint();

    qDebug()<<"labeling enable : "<<vectorLayer->labelsEnabled();
    //



    // Initialize the canvas and set up the tool

    this->setExtent(QgsRectangle(-180, -90, 180, 90)); // Set extent to world bounds
    this->setLayers({vectorLayer,mapLayer});

    // Create and set the drawing tool
    DrawPointTool* drawTool = new DrawPointTool(this);
    drawTool->setLayer(vectorLayer);
    this->setMapTool(drawTool);
    qDebug()<<"maptool set";


    //Setting symbol
    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(vectorLayer->renderer());
    QgsSymbol* symbol = renderer->symbol();

    QgsSimpleMarkerSymbolLayer* markerLayer = dynamic_cast<QgsSimpleMarkerSymbolLayer*>(symbol->symbolLayer(0));
    qDebug()<<(markerLayer == NULL);
    // markerSymbol->setSize(10); // Set size of the triangle
    // markerSymbol->setColor(QColor(255, 0, 0)); //
    markerLayer->setShape(Qgis::MarkerShape::Triangle);
    markerLayer->setSize(5);
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

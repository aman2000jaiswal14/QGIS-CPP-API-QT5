#include "custommapcanvas.h"
#include <QLabel>
#include "qgslabelfeature.h"
#include "qgssinglesymbolrenderer.h"
#include "qgssymbol.h"
#include "qgsmarkersymbol.h"
#include "qgsmarkersymbollayer.h"
#include <QMap>
#include "qgslabellinesettings.h"

CustomMapCanvas::CustomMapCanvas() {
    // this->setCanvasColor(Qt::green);

    // Create a vector layer
    QgsVectorLayer* vectorLayer = new QgsVectorLayer("LineString?crs=EPSG:4326", "PointsLayer", "memory");
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");

    vectorLayer->setCrs(mapLayer->crs());

    // Create fields with data types specified
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
    labelSettings.fieldName =  "\"id\" || ' - ' || \"name\"";
    labelSettings.placement = Qgis::LabelPlacement::Line;
    labelSettings.isExpression= true;
    qDebug()<<"expression : " <<labelSettings.isExpression;

    QgsLabelLineSettings lbLineSetting = labelSettings.lineSettings();
    lbLineSetting.setPlacementFlags(Qgis::LabelLinePlacementFlag::AboveLine);
    labelSettings.setLineSettings(lbLineSetting);


    QgsTextFormat textFormat;
    textFormat.setSize(10);  // Set font size
    textFormat.setColor(QColor(255, 0, 0));  // Set font color to black
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
    //--

    // Line Style

    // --- Create Line Symbol for Rendering ---

    // Create a line symbol


    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(vectorLayer->renderer());

    QgsSymbol* symbol = renderer->symbol();
    QgsLineSymbolLayer *lineLayer = dynamic_cast<QgsLineSymbolLayer*>(symbol->symbolLayer(0));
    qDebug()<<(lineLayer == NULL);
    // markerSymbol->setSize(10); // Set size of the triangle
    // markerSymbol->setColor(QColor(255, 0, 0)); //
    lineLayer->setWidth(0.5);
    lineLayer->setColor(Qt::blue);
    qDebug()<<lineLayer->dxfPenStyle();


    vectorLayer->triggerRepaint();
    // --



    QVector<QgsPointXY> cordpoints;
    cordpoints.append(QgsPointXY(30.22,25.26));
    cordpoints.append(QgsPointXY(102.85,25.71));
    cordpoints.append(QgsPointXY(77.59,5.41));
    QgsGeometry lineGeometry = QgsGeometry::fromPolylineXY(cordpoints);
    QgsFeature feature;
    feature.initAttributes(2);
    // Set attributes - the feature needs to know about the field definitions
    feature.setFields(vectorLayer->fields());  // Set fields from the layer
    feature.setAttribute("id", 1);             // Set 'id' field value
    feature.setAttribute("name", "New Line"); // Set 'name' field value

    // Set the geometry for the feature
    feature.setGeometry(lineGeometry);

    // Print the attribute count (should be 2)
    qDebug() << "Attribute count:" << feature.attributeCount(); // Should output 2

    // Print the attributes for debugging
    qDebug() << "Attribute 0 (id):" << feature.attribute("id");
    qDebug() << "Attribute 1 (name):" << feature.attribute("name");

    vectorLayer->dataProvider()->addFeature(feature);



    // Create and set the drawing tool
    DrawLineStringTool* drawTool = new DrawLineStringTool(this);
    drawTool->setLayer(vectorLayer);
    this->setMapTool(drawTool);
    qDebug()<<"maptool set";



    // Refresh the map canvas to show the labels
    this->refresh();

    // Initialize the canvas and set up the tool

    this->setExtent(QgsRectangle(-180, -90, 180, 90)); // Set extent to world bounds
    this->setLayers({vectorLayer,mapLayer});



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

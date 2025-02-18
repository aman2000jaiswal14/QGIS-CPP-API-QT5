#include "custommapcanvas.h"
#include <QLabel>

#include <QMap>
#include "qgsrasterlayer.h"

/*
  new ImageLayer({
    extent: [-13884991, 2870341, -7455066, 6338219],
    source: new ImageWMS({
      url: 'https://ahocevar.com/geoserver/wms',
      params: {'LAYERS': 'topp:states'},
      ratio: 1,
      serverType: 'geoserver',
    }),
  }),
];
 */
CustomMapCanvas::CustomMapCanvas() {
    // this->setCanvasColor(Qt::green);


    // wms start
/*
    QString wmsUrl = "https://ahocevar.com/geoserver/wms"; // Base URL
    QString wmsLayerName = "topp:states"; // Exact layer name (important!)

    // Construct the WMS URI
    QString uri = QString("%1?SERVICE=WMS&VERSION=1.3.0&REQUEST=GetMap&LAYERS=%2&STYLES=&FORMAT=image/png&CRS=EPSG:4326").arg(wmsUrl, wmsLayerName);

    QgsRasterLayer *wmsLayer = new QgsRasterLayer(uri, wmsLayerName);

    if (wmsLayer->isValid()) {
        qDebug() << "WMS layer loaded successfully!";

    } else {
        qDebug() << "Error loading WMS layer: " << wmsLayer->error().message();
        delete wmsLayer;
    }

*/


    // Layer 1: Pixelmap (TileWMS in JavaScript)
                QString pixelmapUrl = "https://wms.geo.admin.ch/";
    QString pixelmapLayerName = "ch.swisstopo.pixelkarte-farbe-pk1000.noscale";
    QString pixelmapUri = QString("%1?SERVICE=WMS&VERSION=1.3.0&REQUEST=GetMap&LAYERS=%2&FORMAT=image/jpeg&CRS=EPSG:3857").arg(pixelmapUrl, pixelmapLayerName); // Note: EPSG:3857 often used for web maps

    QgsRasterLayer *pixelmapLayer = new QgsRasterLayer(pixelmapUri, "Pixelmap 1:1000000"); // Give it a descriptive name

    if (pixelmapLayer->isValid()) {
        qDebug() << "Pixelmap layer loaded successfully!";

    } else {
        qDebug() << "Error loading pixelmap layer: " << pixelmapLayer->error().message();
        delete pixelmapLayer;
    }


    // Layer 2: Flood Alert (ImageWMS in JavaScript)
    QString floodAlertUrl = "https://wms.geo.admin.ch/";
    QString floodAlertLayerName = "ch.bafu.hydroweb-warnkarte_national";
    QString floodAlertUri = QString("%1?SERVICE=WMS&VERSION=1.3.0&REQUEST=GetMap&LAYERS=%2&FORMAT=image/png&CRS=EPSG:3857").arg(floodAlertUrl, floodAlertLayerName);  // Adjust CRS if needed

    QgsRasterLayer *floodAlertLayer = new QgsRasterLayer(floodAlertUri, "Flood Alert");

    if (floodAlertLayer->isValid()) {
        qDebug() << "Flood alert layer loaded successfully!";


    } else {
        qDebug() << "Error loading flood alert layer: " << floodAlertLayer->error().message();
        delete floodAlertLayer;
    }




    // -- end of wms
    QString svgPath = "/home/aman/map1/plane.svg";

    // Create a vector layer
    QgsVectorLayer* vectorLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");
    QgsVectorLayer* mapLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    // wmsLayer->setCrs(mapLayer->crs());
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

    //

    QgsGeometry pointGeometry = QgsGeometry::fromPointXY(QgsPointXY(29.77,74.88));
    QgsFeature feature;
    feature.initAttributes(2);
    // Set attributes - the feature needs to know about the field definitions
    feature.setFields(vectorLayer->fields());  // Set fields from the layer
    feature.setAttribute("id", 1);             // Set 'id' field value
    feature.setAttribute("name", "New Point"); // Set 'name' field value

    // Set the geometry for the feature
    feature.setGeometry(pointGeometry);

    // Print the attribute count (should be 2)
    qDebug() << "Attribute count:" << feature.attributeCount(); // Should output 2

    // Print the attributes for debugging
    qDebug() << "Attribute 0 (id):" << feature.attribute("id");
    qDebug() << "Attribute 1 (name):" << feature.attribute("name");

    vectorLayer->dataProvider()->addFeature(feature);
    //


    // Check the number of fields
    qDebug() << "Number of fields in vector layer:" << vectorLayer->fields().size();
    qDebug() << "Fields in vector layer:" << vectorLayer->fields();
    for (int i = 0; i < vectorLayer->fields().size(); ++i)
    {
        qDebug() << "Field" << i << ":" << vectorLayer->fields().at(i).name();
    }

    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(vectorLayer->renderer());
    QgsSymbol* symbol = renderer->symbol();


    svgLayer = new QgsSvgMarkerSymbolLayer(svgPath);
    if (svgLayer==NULL) {
        qDebug() << "Error loading SVG file:" << svgPath;
        return;
    }

    connect(this, &QgsMapCanvas::scaleChanged, this, [=](double scale) {
        // Adjust marker size based on the scale of the map
        double zoomFactor = 200000000000.0 / scale ;  // You can fine-tune this factor based on your needs
        qDebug()<<"initial :  "<<zoomFactor<<scale;
        // Set the size of the SVG marker layer relative to zoom
        svgLayer->setSize(qMin(zoomFactor,10.0));  // Multiply by a constant factor to scale

        vectorLayer->triggerRepaint();
    });


    // Initial update when canvas is created
    double initialScale = this->scale();
    double zoomFactor  = 200000000000.0 / initialScale;

    qDebug()<<"initial :  "<<zoomFactor<<initialScale;
    svgLayer->setSize(zoomFactor);  // Adjust the initial size based on zoom level












    // symbol->insertSymbolLayer(0,svgLayer);
    // symbol->appendSymbolLayer(svgLayer);
    symbol->changeSymbolLayer(0,svgLayer);



    // QgsSimpleMarkerSymbolLayer* markerLayer = dynamic_cast<QgsSimpleMarkerSymbolLayer*>(symbol->symbolLayer(0));
    // qDebug()<<(markerLayer == NULL);
    // // markerSymbol->setSize(10); // Set size of the triangle
    // // markerSymbol->setColor(QColor(255, 0, 0)); //
    // markerLayer->setShape(Qgis::MarkerShape::Triangle);
    // markerLayer->setSize(5);
    vectorLayer->triggerRepaint();

    // --- Labeling Setup ---
    // Create label settings
    QgsPalLayerSettings labelSettings;

    // Set the field to be used for labels
    labelSettings.fieldName = "id";  // Use the "name" field for labeling



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
    //




    // Create and set the drawing tool
    DrawPointTool* drawTool = new DrawPointTool(this);
    drawTool->setLayer(vectorLayer);
    this->setMapTool(drawTool);
    qDebug()<<"maptool set";



    // Refresh the map canvas to show the labels
    this->refresh();

    // Initialize the canvas and set up the tool

    this->setExtent(QgsRectangle(-180, -90, 180, 90)); // Set extent to world bounds
    this->setLayers({vectorLayer,pixelmapLayer,floodAlertLayer,mapLayer});


    // Zoom to the flood alert layer's extent:
    if (floodAlertLayer->isValid()) { // Check if the layer is valid
        QgsRectangle extent = floodAlertLayer->extent(); // Get the extent of the flood alert layer

        if (!extent.isNull()) { // Check if the extent is valid (not null)
            this->setExtent(extent); // Set the canvas extent to the layer's extent
            this->refresh(); // Refresh the canvas to show the new extent
        } else {
            qDebug() << "Flood alert layer extent is invalid (null).";
            this->zoomToFullExtent(); // Fallback to full extent if extent is invalid
        }
    } else {
        qDebug() << "Flood alert layer is not valid. Cannot zoom to extent.";
        this->zoomToFullExtent(); // Fallback to full extent if layer is invalid
    }




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

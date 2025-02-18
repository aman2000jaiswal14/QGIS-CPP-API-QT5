#include "drawpointtool.h"

DrawPointTool::DrawPointTool(QgsMapCanvas *canvas)
    : QgsMapTool(canvas), mCanvas(canvas) {}

void DrawPointTool::canvasPressEvent(QgsMapMouseEvent *e)
{
    qDebug() << "pressed";

    // Convert screen coordinates to map coordinates
    QgsPointXY mapPoint = mCanvas->getCoordinateTransform()->toMapCoordinates(e->pos());

    double latitude = mapPoint.y();
    double longitude = mapPoint.x();

    qDebug() << "Latitude: " << latitude << ", Longitude: " << longitude;

    // Create a point geometry
    QgsGeometry pointGeometry = QgsGeometry::fromPointXY(mapPoint);

    // Create a feature
    QgsFeature feature;
    feature.initAttributes(2);
    feature.setFields(mLayer->fields());
    feature.setAttribute("id", 2);             // Set 'id' field value
    feature.setAttribute("name", "New Point"); // Set 'name' field value

    feature.setGeometry(pointGeometry);

    qDebug() << "Attribute count:" << feature.attributeCount(); // Output should be 2

    // Print the attributes for debugging
    qDebug() << "Attribute 0:" << feature.attribute(0);
    qDebug() << "Attribute 1:" << feature.attribute(1);

    QgsFeatureList featureList;
    featureList.append(feature);

    // Add the feature to the vector layer
    mLayer->dataProvider()->addFeatures(featureList);

    // Refresh only the layer to reflect the changes
    mLayer->triggerRepaint();
}

void DrawPointTool::setLayer(QgsVectorLayer *layer) {
    mLayer = layer;
}

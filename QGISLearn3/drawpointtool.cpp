#include "drawpointtool.h"

DrawPointTool::DrawPointTool(QgsMapCanvas *canvas)
    : QgsMapTool(canvas), mCanvas(canvas) {}

void DrawPointTool::canvasPressEvent(QgsMapMouseEvent *e)
{
    qDebug()<<"pressed";
    // Convert screen coordinates to map coordinates
    QgsPointXY mapPoint = mCanvas->getCoordinateTransform()->toMapCoordinates(e->pos());
    double latitude = mapPoint.y();
    double longitude = mapPoint.x();
    qDebug() << "Latitude: " << latitude << ", Longitude: " << longitude;
    // Create a point geometry
    QgsGeometry pointGeometry = QgsGeometry::fromPointXY(mapPoint);

    // Create a feature
    QgsFeature feature;
    feature.setAttribute("name","New Point");
    feature.setAttribute("latitude", latitude);
    feature.setAttribute("longitude", longitude);
    feature.setGeometry(pointGeometry);
    QgsFeatureList featureList;
    featureList.append(feature);
    // Add the feature to the vector layer
    mLayer->dataProvider()->addFeatures(featureList);

    QString labelText = QString("Lat: %1, Long: %2").arg(latitude).arg(longitude);



    mCanvas->refresh();
}

void DrawPointTool::setLayer(QgsVectorLayer *layer) {
    mLayer = layer;
}

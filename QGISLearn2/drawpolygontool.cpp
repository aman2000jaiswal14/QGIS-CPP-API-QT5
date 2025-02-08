#include "drawpolygontool.h"



DrawPolygonTool::DrawPolygonTool(QgsMapCanvas *canvas)
    : QgsMapTool(canvas), mCanvas(canvas), mInProgress(false) {


}

void DrawPolygonTool::canvasPressEvent(QgsMapMouseEvent *e) {

    if(e->button()==Qt::LeftButton)
    {
    if (!mInProgress) {
        mInProgress = true;
        mVertices.clear(); // Start a new polygon
    }

    // Convert screen coordinates to map coordinates
    QgsPointXY mapPoint = mCanvas->getCoordinateTransform()->toMapCoordinates(e->pos());
    mVertices.append(mapPoint);

    // Draw temporary line or shape to visualize the polygon being drawn
    drawTemporaryPolygon();

    qDebug() << "Added point at Latitude:" << mapPoint.y() << ", Longitude:" << mapPoint.x();
    }

}

void DrawPolygonTool::canvasReleaseEvent(QgsMapMouseEvent *e)
{
    if (e->button() == Qt::RightButton && !(e->modifiers() & Qt::ControlModifier)) { // Single Right Click
        finishPolygon();
    }
}

void DrawPolygonTool::setLayer(QgsVectorLayer *layer) {
    mLayer = layer;
       setPolygonTransparency(0.4);
}

void DrawPolygonTool::drawTemporaryPolygon() {

    if (mLayer == nullptr) return;

    // Create a QgsPolygonXY by wrapping mVertices in a QVector
    QVector<QVector<QgsPointXY>> polygonParts;
    polygonParts.append(QVector<QgsPointXY>::fromList(mVertices));  // Wrap mVertices in a QVector

    // Create the geometry for the polygon
    QgsGeometry geom = QgsGeometry::fromPolygonXY(polygonParts);

    QgsFeature newFeature;
    newFeature.setId(countid++);
    newFeature.setGeometry(geom);



    // Add the temporary feature to the layer, if it is not already added
    if (mLayer->featureCount() == 0) {
        mLayer->dataProvider()->addFeature(newFeature);
        mTemporaryFeature = newFeature;

    } else {
        // If there is already a temporary feature, remove it before adding the updated one
        mLayer->dataProvider()->deleteFeatures({mTemporaryFeature.id()});
        mLayer->dataProvider()->addFeature(newFeature);
        mTemporaryFeature = newFeature;
    }




    mCanvas->refresh();

}

void DrawPolygonTool::finishPolygon() {
    if (mVertices.size() < 3) return; // Not enough points to form a polygon

    // Create a QgsPolygonXY by wrapping mVertices in a QVector
    QVector<QVector<QgsPointXY>> polygonParts;
    polygonParts.append(QVector<QgsPointXY>::fromList(mVertices));  // Wrap mVertices in a QVector

    // Create the polygon geometry
    QgsGeometry polygonGeometry = QgsGeometry::fromPolygonXY(polygonParts);

    // Create a feature for the polygon
    QgsFeature feature;
    feature.setId(countid++);
    feature.setGeometry(polygonGeometry);

    // Add the polygon to the layer
    mLayer->dataProvider()->addFeature(feature);


    // Clear vertices and end polygon drawing, allow new polygon
    mVertices.clear();
    mInProgress = false;
    // Now delete the temporary feature
    if (mLayer->featureCount() > 0) {
        mLayer->dataProvider()->deleteFeatures({mTemporaryFeature.id()});
    }
    qDebug()<<"Total features: "<<mLayer->featureCount();

    mCanvas->refresh();
}

void DrawPolygonTool::setPolygonTransparency(double transparency) {
    if (!mLayer) return;

    // 1. Get the renderer (or create one if it doesn't exist)
    QgsSingleSymbolRenderer* renderer = dynamic_cast<QgsSingleSymbolRenderer*>(mLayer->renderer());

    if (!renderer) {
        // Create a new renderer with a default symbol
        renderer = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mLayer->geometryType()));
        mLayer->setRenderer(renderer); // Set the new renderer to the layer
    }

    // 2. Get the symbol (or create a copy if it doesn't exist)
    QgsSymbol* symbol = renderer->symbol();
    if (!symbol) {
        symbol = QgsSymbol::defaultSymbol(mLayer->geometryType())->clone(); // Clone a default symbol
    }
    else
    {
        symbol = symbol->clone();//clone the symbol before modifying it
    }


    // 3. Calculate and set opacity

    symbol->setOpacity(transparency);
    symbol->setColor(Qt::yellow);

    // 4. Set the symbol back to the renderer
    renderer->setSymbol(symbol);

    // 5. Trigger repaint
    mLayer->triggerRepaint();
}

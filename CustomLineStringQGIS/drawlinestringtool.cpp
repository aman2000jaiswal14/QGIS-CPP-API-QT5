#include "drawlinestringtool.h"

DrawLineStringTool::DrawLineStringTool(QgsMapCanvas *canvas) : QgsMapTool(canvas), mCanvas(canvas), mInProgress(false) {

    setCursor(Qt::CrossCursor);

}

void DrawLineStringTool::canvasPressEvent(QgsMapMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        if (!mInProgress) {
            mInProgress = true;
            m_points.clear(); // Start a new polygon
        }




        QgsPointXY clickedPoint = mCanvas->getCoordinateTransform()->toMapCoordinates(e->pos());

        // Add the clicked point to the line geometry
        m_points.append(clickedPoint);

        // Update the geometry of the line (temporary line)
        QgsGeometry lineGeometry = QgsGeometry::fromPolylineXY(m_points);
        m_currentFeature.setGeometry(lineGeometry);


        // Create a temporary feature with the updated geometry


        mLayer->dataProvider()->deleteFeatures({m_tempFeature.id()});
        m_tempFeature.setGeometry(lineGeometry);
        mLayer->dataProvider()->addFeature(m_tempFeature);

        // Redraw the canvas to show the temporary line
        mCanvas->refresh();

        qDebug() << "Added point at Latitude:" << clickedPoint.y() << ", Longitude:" << clickedPoint.x();
    }
}

void DrawLineStringTool::canvasReleaseEvent(QgsMapMouseEvent *e)
{
    if (e->button() == Qt::RightButton && !(e->modifiers() & Qt::ControlModifier)) { // Single Right Click
        finishLine();
        // Reset points and feature to start a new line after finishing
        m_points.clear();
        m_currentFeature.setGeometry(QgsGeometry());

        // Disable the tool once the line is finalized
        mInProgress = false;

    }
    qDebug()<<"temp feature id : "<<m_tempFeature.id();
    qDebug()<<"feature count : "<<mLayer->featureCount();
}

void DrawLineStringTool::setLayer(QgsVectorLayer *layer)
{
    mLayer = layer;
    m_tempFeature.setGeometry(QgsGeometry());
    mLayer->dataProvider()->addFeature(m_tempFeature);
}

void DrawLineStringTool::drawTemporaryLine()
{

}

void DrawLineStringTool::finishLine()
{
    if (m_points.size() > 1)
    {

        // Add the feature to the layer's data provider

        m_currentFeature.initAttributes(2);
        // Set attributes - the feature needs to know about the field definitions
        m_currentFeature.setFields(mLayer->fields());  // Set fields from the layer
        m_currentFeature.setAttribute("id", nextFeatureId++);             // Set 'id' field value
        m_currentFeature.setAttribute("name", "Line"); // Set 'name' field value

        qDebug()<<"current feature id : "<<m_currentFeature.id();
        // Print the attribute count (should be 2)
        qDebug() << "Attribute count:" << m_currentFeature.attributeCount(); // Should output 2

        // Print the attributes for debugging
        qDebug() << "Attribute 0 (id):" << m_currentFeature.attribute("id");
        qDebug() << "Attribute 1 (name):" << m_currentFeature.attribute("name");

        mLayer->dataProvider()->addFeature(m_currentFeature);

        // Refresh the canvas to display the finalized line
        mCanvas->refresh();
    }
    else
    {
        qDebug() << "Line not long enough to add to layer";
    }
}

void DrawLineStringTool::setTemporaryRenderer()
{
    // Set the line symbol for temporary rendering
    // QgsSymbol* lineSymbol = QgsSymbol::createSimple({{"color", "red"}, {"width", "2"}});
    // QgsSingleSymbolRenderer* renderer = new QgsSingleSymbolRenderer(lineSymbol);

    // Set the temporary renderer for the vector layer
    // m_vectorLayer->setRenderer(renderer);
}


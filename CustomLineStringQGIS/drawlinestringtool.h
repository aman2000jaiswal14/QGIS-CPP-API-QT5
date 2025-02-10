#ifndef DRAWLINESTRINGTOOL_H
#define DRAWLINESTRINGTOOL_H

#include <QObject>
#include <QWidget>
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include <qgspoint.h>
#include <qgsvectorlayer.h>
#include <qgsfeature.h>
#include <qgsgeometry.h>
#include <qgsfield.h>
#include <QVariant>
#include <qgspointxy.h>
#include <qgsmapmouseevent.h>
#include "qgssymbol.h"
class DrawLineStringTool : public QgsMapTool
{
    Q_OBJECT
public:
    DrawLineStringTool(QgsMapCanvas* canvas);

    void canvasPressEvent(QgsMapMouseEvent* e);
    void canvasReleaseEvent(QgsMapMouseEvent *e) override;
    void setLayer(QgsVectorLayer* layer);

private:
    void drawTemporaryLine();
    int nextFeatureId = 1;
    void finishLine();
    // Set up temporary rendering for the line
    void setTemporaryRenderer();


private:
    QgsMapCanvas *mCanvas;
    QgsVectorLayer *mLayer = nullptr;
    bool mInProgress;  // Flag to track whether we are drawing a line
    QVector<QgsPointXY> m_points;  // Store points for the line geometry
    QgsFeature m_currentFeature;    // Feature to hold the line geometry
    QgsFeature m_tempFeature;      // Temporary feature for real-time rendering
};

#endif // DRAWLINESTRINGTOOL_H

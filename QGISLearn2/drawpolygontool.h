#ifndef DRAWPOLYGONTOOL_H
#define DRAWPOLYGONTOOL_H

#include <QObject>
#include <QWidget>
#include "qgsmaptool.h"
#include "qgsvectorlayer.h"
#include <QPolygonF>
#include <QPointF>
#include "qgsmapcanvas.h"
#include <QVariant>
#include <qgspointxy.h>
#include <qgsmapmouseevent.h>
#include "qgssymbol.h"

#include "qgssinglesymbolrenderer.h"
#include "qgsrulebasedrenderer.h"



class DrawPolygonTool : public QgsMapTool {
public:
    DrawPolygonTool(QgsMapCanvas *canvas);
    long countid = 0;
    void canvasPressEvent(QgsMapMouseEvent *e) override;
    void canvasReleaseEvent(QgsMapMouseEvent *e) override;

    void setLayer(QgsVectorLayer *layer);

private:
    void drawTemporaryPolygon();

    void finishPolygon();

    void setPolygonTransparency(double transparency);

    QgsMapCanvas *mCanvas;
    QgsVectorLayer *mLayer = nullptr;
    QList<QgsPointXY> mVertices;  // Stores the points for the polygon
    bool mInProgress;  // Flag to track whether we are drawing a polygon

private:
    QgsFeature mTemporaryFeature;
};

#endif // DRAWPOLYGONTOOL_H

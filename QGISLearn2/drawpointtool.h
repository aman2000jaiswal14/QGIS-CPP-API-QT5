#ifndef DRAWPOINTTOOL_H
#define DRAWPOINTTOOL_H

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

class DrawPointTool : public QgsMapTool
{
    Q_OBJECT

public:
    DrawPointTool(QgsMapCanvas* canvas);

    // This method will be triggered on mouse click.



    void canvasPressEvent(QgsMapMouseEvent* e);

    void setLayer(QgsVectorLayer* layer);

private:
    QgsMapCanvas* mCanvas;
    QgsVectorLayer* mLayer;  // The layer where the point will be drawn
};
#endif // DRAWPOINTTOOL_H

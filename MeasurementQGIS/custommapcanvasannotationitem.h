#ifndef CUSTOMMAPCANVASANNOTATIONITEM_H
#define CUSTOMMAPCANVASANNOTATIONITEM_H

#include "qgsmapcanvasannotationitem.h"
#include "qgsmapcanvas.h"
#include <QPainter>
#include "qgsannotation.h"

class CustomMapCanvasAnnotationItem : public QgsMapCanvasAnnotationItem
{
public:
    CustomMapCanvasAnnotationItem(QgsAnnotation *annotation, QgsMapCanvas *mapCanvas);
    void paint(QPainter *painter) override;
private :
    QRectF mBoundingRect;
};
#endif // CUSTOMMAPCANVASANNOTATIONITEM_H

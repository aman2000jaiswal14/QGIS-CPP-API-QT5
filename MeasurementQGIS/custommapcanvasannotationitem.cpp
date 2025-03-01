#include "custommapcanvasannotationitem.h"


CustomMapCanvasAnnotationItem::CustomMapCanvasAnnotationItem(QgsAnnotation *annotation, QgsMapCanvas *mapCanvas)
    : QgsMapCanvasAnnotationItem(annotation, mapCanvas)
{
    // You can add additional initialization logic here if needed
}

void CustomMapCanvasAnnotationItem::paint(QPainter *painter)
{
    QgsAnnotation *mAnnotation = annotation();
    if ( !mAnnotation || !mAnnotation->isVisible() )
        return;


    QgsRenderContext rc = QgsRenderContext::fromQPainter( painter );
    rc.setFlag( Qgis::RenderContextFlag::Antialiasing, true );

    if ( mAnnotation )
        mAnnotation->render( rc );

    if ( isSelected() )
    {
        // drawSelectionBoxes( painter );
    }
}

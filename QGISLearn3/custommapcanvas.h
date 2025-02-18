#ifndef CUSTOMMAPCANVAS_H
#define CUSTOMMAPCANVAS_H

#include <QObject>
#include <QWidget>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <drawpointtool.h>
#include "qgslabelfeature.h"
#include "qgssinglesymbolrenderer.h"
#include "qgssymbol.h"
#include "qgsmarkersymbol.h"
#include "qgsmarkersymbollayer.h"
class CustomMapCanvas : public QgsMapCanvas
{
    Q_OBJECT

    QgsSvgMarkerSymbolLayer* svgLayer;
public:
    CustomMapCanvas();

private :

};

#endif // CUSTOMMAPCANVAS_H

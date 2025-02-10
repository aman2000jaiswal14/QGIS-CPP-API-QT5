#ifndef CUSTOMMAPCANVAS_H
#define CUSTOMMAPCANVAS_H

#include <QObject>
#include <QWidget>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <drawpointtool.h>
#include "qgssymbol.h"
#include "qgssinglesymbolrenderer.h"
#include "qgsmarkersymbollayer.h"
class CustomMapCanvas : public QgsMapCanvas
{
    Q_OBJECT
public:
    CustomMapCanvas();

private :

};

#endif // CUSTOMMAPCANVAS_H

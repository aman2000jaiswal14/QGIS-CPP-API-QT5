#ifndef CUSTOMMAPCANVAS_H
#define CUSTOMMAPCANVAS_H

#include <QObject>
#include <QWidget>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include "datamanager.h"
#include <QMenu>
#include <QAction>

class CustomMapCanvas : public QgsMapCanvas
{
    Q_OBJECT


public:
    CustomMapCanvas();



private :
    QgsProject *project;
public slots:
    void xyCoordinateSlot(QgsPointXY);
    void scaleChangedSlot(double scale);
signals:
    void xyCoordinatesSignal(QgsPointXY);
    void scaleLabelSignal(double scale);

};

#endif // CUSTOMMAPCANVAS_H

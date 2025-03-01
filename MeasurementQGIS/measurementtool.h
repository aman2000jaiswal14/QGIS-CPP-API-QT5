#ifndef MEASUREMENTTOOL_H
#define MEASUREMENTTOOL_H
#include "qgsmaptoolemitpoint.h"
#include <QObject>
#include "qgspointxy.h"
#include "qgsmapmouseevent.h"
#include "qgsdistancearea.h"
#include "qgsmapcanvas.h"
#include <QDebug>
#include "qgsrubberband.h"
#include "qgsannotation.h"
#include "qgstextannotation.h"
#include "qgssnappingconfig.h"
#include "qgssnappingutils.h"
#include "qgsannotationlayer.h"
#include "qgsannotationitem.h"
#include "qgsannotationlinetextitem.h"
#include "qgslinestring.h"
class MeasurementTool : public QgsMapToolEmitPoint
{
    Q_OBJECT

public:
    MeasurementTool(QgsMapCanvas* canvas, QgsAnnotationLayer *annotationLayer)
        : QgsMapToolEmitPoint(canvas), mCanvas(canvas), mAnnotationLayer(annotationLayer)
    {
        // Set the cursor for the measurement tool
        setCursor(Qt::CrossCursor);
        linestring = new QgsLineString;
        linetext = new QgsAnnotationLineTextItem(QString("Distance: %1 km").arg(mDistance, 0, 'f', 2),linestring);
        mAnnotationLayer->addItem(linetext);
        // Initialize rubber band for drawing the line
        mRubberBand = new QgsRubberBand(canvas, Qgis::GeometryType::Line);
        mRubberBand->setColor(Qt::red);
        mRubberBand->setWidth(2);

        // Initialize text annotation for displaying distance
        mDistanceAnnotation = new QgsTextAnnotation();

        mDistanceAnnotation->setFrameSize(QSizeF(100, 50));
        // mDistanceAnnotation->setFrameBackgroundColor(Qt::white);
        // mDistanceAnnotation->setFrameBorderWidth(1);
        // mDistanceAnnotation->setFrameBorderColor(Qt::black);
        mDistanceAnnotation->setHasFixedMapPosition(true);
    }

    void canvasReleaseEvent(QgsMapMouseEvent* e) override
    {
        // Get the clicked point in map coordinates
        QgsPointXY point = toMapCoordinates(e->pos());

        if (e->button() == Qt::LeftButton)
        {
            if (mPoints.isEmpty())
            {
                // First point
                mPoints.append(point);
                mRubberBand->addPoint(point);

                qDebug() << "First point:" << point.toString();
            }
            else
            {
                // Second point
                mPoints.append(point);
                mRubberBand->addPoint(point);

                qDebug() << "latest point:" << point.toString();

                // Calculate the distance between the two points
                calculateDistance();

                // Draw the line and display the distance label
                drawLineWithLabel();


            }

        }
        else if(e->button() == Qt::RightButton)
        {
            // Reset for the next measurement
            mDistance = 0;
            linestring->clear();
            mPoints.clear();
            mRubberBand->reset();
            mAnnotationLayer->triggerRepaint();
        }

    }

    void drawLineWithLabel()
    {
        // Draw the line using the rubber band
        mRubberBand->show();
        linestring->clear();

        linestring->addVertex(QgsPoint(mPoints[mPoints.size()/2-1]));
        linestring->addVertex(QgsPoint(mPoints[mPoints.size()/2]));
        linetext->setText(QString("Distance: %1 km").arg(mDistance, 0, 'f', 2));
        mAnnotationLayer->triggerRepaint();

    }
    ~MeasurementTool()
    {
        delete mRubberBand;
        delete mDistanceAnnotation;
    }

private:
    void calculateDistance()
    {
        if (mPoints.size() < 2)
            return;

        // Create a QgsDistanceArea object
        QgsDistanceArea distanceCalculator;

        // Set the ellipsoid (e.g., WGS84)
        distanceCalculator.setEllipsoid("WGS84");

        // Set the source CRS (Coordinate Reference System) of the map canvas
        QgsCoordinateReferenceSystem canvasCrs = mCanvas->mapSettings().destinationCrs();
        distanceCalculator.setSourceCrs(canvasCrs, QgsProject::instance()->transformContext());

        // Calculate the distance between the two points

        double distanceBetweenLastTwoPoint = distanceCalculator.measureLine(mPoints[mPoints.size()-2], mPoints[mPoints.size()-1]);

        // Convert the distance to kilometers
        mDistance += distanceCalculator.convertLengthMeasurement(distanceBetweenLastTwoPoint, Qgis::DistanceUnit::Kilometers);

        // Output the distance
        qDebug() << "Distance between the points:" << mDistance << "km";
    }
    double distanceBetweenTwoPoint(QgsPointXY point1, QgsPointXY point2)
    {
        // Create a QgsDistanceArea object
        QgsDistanceArea distanceCalculator;

        // Set the ellipsoid (optional, but recommended for accurate distance calculations)
        distanceCalculator.setEllipsoid("WGS84");

        // Calculate the distance between the two points
        double distance = distanceCalculator.measureLine(point1, point2);

        // Convert the distance to kilometers (if needed)
        distance = distanceCalculator.convertLengthMeasurement(distance, Qgis::DistanceUnit::Kilometers);

        // Output the distance
        // qDebug() << "Distance between the two points:" << distance << "km";
        return distance;
    }

    QgsMapCanvas* mCanvas;
    QgsAnnotationLayer *mAnnotationLayer;
    QVector<QgsPointXY> mPoints; // Stores the clicked points
    QgsRubberBand* mRubberBand; // For drawing the line
    QgsTextAnnotation* mDistanceAnnotation; // For displaying the distance label
    double mDistance = 0; // Stores the calculated distance
    QgsLineString *linestring;
    QgsAnnotationLineTextItem *linetext;
};

#endif // MEASUREMENTTOOL_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgspointxy.h"
#include <QDebug>
#include "qgsdistancearea.h"
#include "qgsunittypes.h"
#include "qgsrasterlayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayer.h"
#include "qgsmapcanvas.h"
#include "measurementtool.h"

#include "qgstextannotation.h"
#include "qgsproject.h"
#include "qgsannotationmanager.h"
#include "qgsmapcanvasannotationitem.h"
#include "custommapcanvasannotationitem.h"
#include "qgsannotationlayer.h"
#include "qgsannotationitem.h"
#include "qgsannotationlinetextitem.h"
#include "qgslinestring.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QgsMapCanvas *canvas;
    QgsVectorLayer *baselayer;
    QgsVectorLayer *pointFeatureLayer;
    MeasurementTool *measurementTool;
    QgsAnnotationLayer *annotationLayer;

};

// Custom text annotation item
class TextAnnotationItem : public QgsAnnotationItem {
public:
    TextAnnotationItem(const QString &text, const QgsPointXY &position, const QFont &font, const QColor &color)
        : mText(text), mPosition(position), mFont(font), mColor(color) {}

    QgsRectangle boundingBox() const override {
        // Define a bounding box for the text
        return QgsRectangle(mPosition.x(), mPosition.y(), mPosition.x() + 100, mPosition.y() + 50);
    }

    void render(QgsRenderContext &context, QgsFeedback *feedback = nullptr) override {
        Q_UNUSED(feedback);

        // Get the QPainter from the render context
        QPainter *painter = context.painter();

        // Set font and color
        painter->setFont(mFont);
        painter->setPen(mColor);

        // Convert the map position to screen coordinates
        QPointF screenPoint = context.mapToPixel().transform(mPosition).toQPointF();

        // Draw the text
        painter->drawText(screenPoint, mText);
    }

private:
    QString mText;
    QgsPointXY mPosition;
    QFont mFont;
    QColor mColor;
};
#endif // MAINWINDOW_H

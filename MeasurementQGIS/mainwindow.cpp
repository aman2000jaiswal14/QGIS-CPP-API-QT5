#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    canvas = new QgsMapCanvas;
    baselayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg","world map","ogr");
    pointFeatureLayer = new QgsVectorLayer("Point?crs=EPSG:4326", "PointsLayer", "memory");




    //############# ADDING rubberband polygon
    //#########################################
    QgsRubberBand *rubberBand = new QgsRubberBand(canvas, Qgis::GeometryType::Polygon);

    // Set the color for the polygon border (optional)
    rubberBand->setColor(Qt::blue);

    // Set the fill color for the polygon (optional)
    rubberBand->setFillColor(QColor(0, 0, 255, 50));  // Blue with 50% opacity

    // Set the width of the polygon border (optional)
    rubberBand->setWidth(1);

    // Add points to the polygon (you can add any number of points to form the polygon)
    rubberBand->addPoint(QgsPointXY(61, 43));
    rubberBand->addPoint(QgsPointXY(63, 43));
    rubberBand->addPoint(QgsPointXY(63, 41));
    rubberBand->addPoint(QgsPointXY(61, 41));
    rubberBand->show();
    //###################################

    //############# ADDING rubberband polygon
    //#########################################
    QgsRubberBand *rubberBandLine = new QgsRubberBand(canvas, Qgis::GeometryType::Line);

    // Set the color for the polygon border (optional)
    rubberBandLine->setColor(Qt::red);

    // Set the fill color for the polygon (optional)
    // rubberBand->setFillColor(QColor(0, 0, 255, 50));  // Blue with 50% opacity

    // Set the width of the polygon border (optional)
    rubberBandLine->setWidth(1);

    // Add points to the polygon (you can add any number of points to form the polygon)
    rubberBandLine->addPoint(QgsPointXY(51, 43));
    rubberBandLine->addPoint(QgsPointXY(52, 43));
    rubberBandLine->addPoint(QgsPointXY(55, 41));
    rubberBandLine->addPoint(QgsPointXY(56, 41));
    rubberBandLine->addPoint(QgsPointXY(57, 41));
    QgsLineString *linestring = new QgsLineString;
    linestring->addVertex(QgsPoint(51, 43));
    linestring->addVertex(QgsPoint(52, 43));
    linestring->addVertex(QgsPoint(55, 41));
    linestring->addVertex(QgsPoint(56, 41));
    linestring->addVertex(QgsPoint(57, 41));
    rubberBandLine->show();
    //###################################



    //############# ADDING Annotation to canvas
    //#########################################
    QgsTextAnnotation* label = new QgsTextAnnotation();

    // Step 3: Set the label text and position
    QString labelText = "My Polygon";
    QgsPointXY labelPosition = QgsPointXY(62, 42);  // You can set this to the center of the polygon, or any position you prefer
    label->setMapPosition(labelPosition);
    label->setDocument(new QTextDocument(labelText));
     // Set the border width of the frame
    label->setFrameSize(QSizeF(100, 30));  // Size of the label box

    // Step 5: Add the annotation (label) to the canvas
    QgsMapCanvasAnnotationItem* annotationItem = new QgsMapCanvasAnnotationItem(label,canvas);
    // CustomMapCanvasAnnotationItem* annotationItem = new CustomMapCanvasAnnotationItem(label,canvas);
    //#########################################




    //############# ADDING Annotation to annotation Layer
    //#########################################

    // Create a custom text annotation item
    QFont font("Arial", 12);
    QColor color(Qt::blue);
    QgsCoordinateTransformContext transformContext;
    QgsAnnotationLayer::LayerOptions layerOptions(transformContext);
    annotationLayer = new QgsAnnotationLayer("Text Annotation Layer", layerOptions);
    QgsAnnotationLineTextItem *linetext = new QgsAnnotationLineTextItem("hello",linestring);
    // linetext->set
    annotationLayer->addItem(linetext);


    //#########################################





    //############# ADDING Measurement tool
    //#########################################
    measurementTool = new MeasurementTool(canvas,annotationLayer);
    canvas->setMapTool(measurementTool);


    //#########################################

    canvas->setLayers({annotationLayer,baselayer});
    // canvas->setExtent(baselayer->extent());

    QgsRectangle newExtent(labelPosition.x() - 2, labelPosition.y() - 2, labelPosition.x() + 2, labelPosition.y() + 2);
    canvas->setExtent(newExtent);

    canvas->refresh();
    setCentralWidget(canvas);

















}

MainWindow::~MainWindow()
{
    delete ui;
}


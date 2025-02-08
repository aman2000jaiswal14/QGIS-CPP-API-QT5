#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    QgsMapCanvas* canvas = new QgsMapCanvas();
    canvas->setCanvasColor(Qt::white);

    // Load the world_map.gpkg as a vector layer
    QgsVectorLayer* layer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");

    if (!layer->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }

    // Add layer to the map canvas
    layerTree = new QgsLayerTree();
    layerTree->addLayer(layer);
    canvas->setLayers({ layer });


    // Set extent of the map to the layer's extent
    canvas->setExtent(layer->extent());

    // Show map on the canvas
    canvas->show();

    setCentralWidget(canvas);

    // Create a label to display the latitude and longitude
    QLabel* coordinatesLabel = new QLabel(this);
    coordinatesLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    coordinatesLabel->setStyleSheet("color: black; background-color: rgba(255, 255, 255, 200); padding: 5px;");
    coordinatesLabel->setFixedWidth(200);
    coordinatesLabel->setFixedHeight(30);
    coordinatesLabel->move(10, height() - 40); // Position it in the bottom left
    coordinatesLabel->show();

    // Connect the canvas mouseMoveEvent to a slot to display coordinates
    connect(canvas, &QgsMapCanvas::xyCoordinates, this, [=](QgsPointXY coordinates) {
        // Convert the coordinates to lat/lon (EPSG:4326)
        QgsCoordinateReferenceSystem crs = layer->crs();
        QgsCoordinateTransform transform(crs, QgsCoordinateReferenceSystem("EPSG:4326"), QgsProject::instance());

        QgsPointXY lonLat = transform.transform(coordinates);
        double latitude = lonLat.y();
        double longitude = lonLat.x();

        // Update the label with the coordinates
        coordinatesLabel->setText(QString("Lat: %1, Lon: %2").arg(latitude).arg(longitude));
    });

}

MainWindow::~MainWindow()
{
    delete ui;

}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qDebug()<<"In MainWindow";
    // Initialize QGIS application
    QgsApplication::setPrefixPath("/path/to/qgis", true); // Set the path to your QGIS installation
    QgsApplication::init();

    // Create map canvas
    canvas = new QgsMapCanvas(this);
    setCentralWidget(canvas);  // Make the canvas the main widget

    // Load a raster image (GeoTIFF)
    QString filePath = "/home/aman/QGIS_PROJECT/LoadRasterMap/land_shallow_topo_2048.tif";//QFileDialog::getOpenFileName(this, "Open TIFF File", "", "TIFF Files (*.tiff *.tif)");
    qDebug()<<filePath;
    if (!filePath.isEmpty()) {
        loadImage(filePath);
    }
}

void MainWindow::loadImage(const QString &filePath)
{
    // Load the raster layer from the TIFF file
    rasterLayer = new QgsRasterLayer(filePath, "Raster Layer");

    if (rasterLayer->isValid()) {
        // Add the layer to the map canvas
        canvas->setLayers({rasterLayer});
        canvas->zoomToFullExtent(); // Fit the layer to the canvas
    } else {
        // Show an error message if the layer is invalid
        QMessageBox::critical(this, "Error", "Failed to load the TIFF file.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    QgsApplication::exit();
}

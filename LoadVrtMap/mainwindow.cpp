#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgsvectorlayer.h"
#include "qgsrasterlayer.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("vrt map");

    canvas = new QgsMapCanvas(this);
    // canvas->setCanvasColor(Qt::white);
    setCentralWidget(canvas);

    QgsRasterLayer *rasterLayer = new QgsRasterLayer("/home/aman/map1/map1.vrt", "Raster Layer");

    if (rasterLayer->isValid()) {
        // Add the layer to the map canvas
        canvas->setLayers({rasterLayer});
        canvas->zoomToFullExtent(); // Fit the layer to the canvas
    } else {
        // Show an error message if the layer is invalid
        QString errorMessage = rasterLayer->dataProvider()->error().message();
        QMessageBox::critical(this, "Error", "Failed to load the VRT file: " + errorMessage);
        // QMessageBox::critical(this, "Error", "Failed to load the TIFF file.");
    }





}

MainWindow::~MainWindow()
{
    delete ui;
}

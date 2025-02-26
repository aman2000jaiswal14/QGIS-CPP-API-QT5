#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "qgssinglebandgrayrenderer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = new QgsMapCanvas;
    setWindowState(Qt::WindowFullScreen);

    // Enable caching and double buffering
    canvas->setCachingEnabled(true);
    canvas->setCanvasColor(Qt::white); // Set a background color
    canvas->enableAntiAliasing(true); // Enable anti-aliasing
    canvas->setParallelRenderingEnabled(true); // Enable parallel rendering . This will solve the problem of flickering


    QList<QgsMapLayer *> layerlist;
    QgsRasterLayer *baseLayer = new QgsRasterLayer("/home/aman/DroneProject/DroneProjectExport/DroneQGISProjectMain/crl_p1.tif", "crl", "gdal");

    if (baseLayer->isValid()) {
        // Build overviews (pyramids) for the raster layer
        // baseLayer->dataProvider()->buildPyramids();

        // Use a single-band gray renderer for better performance
        QgsSingleBandGrayRenderer *renderer = new QgsSingleBandGrayRenderer(baseLayer->dataProvider(), 1); // for grayscale
        baseLayer->setRenderer(renderer);

        layerlist.append(baseLayer);
    } else {
        qDebug() << "Failed to load the TIFF file.------------------------------------------------";
        qDebug() << baseLayer->error().message();
    }

    canvas->setExtent(baseLayer->extent()); // Set extent to layer bounds
    canvas->setDestinationCrs(baseLayer->crs()); // Set the CRS of the canvas
    canvas->setLayers(layerlist);

    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

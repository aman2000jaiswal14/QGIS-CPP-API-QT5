#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgslightsource.h"
#include <qgsflatterraingenerator.h> // Include for QgsFlatTerrainGenerator
#include <qgsvector3d.h> // Include for QgsVector3D
#include <qgspointxy.h> // Include for QgsPointXY
#include <QDebug>
#include <QMessageBox>
#include <QSurfaceFormat>
#include "qgssymbol.h"
#include "qgs3dmapscene.h"
#include "Qt3DExtras"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the main window
    setWindowTitle("QGIS 3D Map Example");
    resize(800, 600);

    // Set OpenGL version to 4.2 (or higher)
    QSurfaceFormat format;
    format.setVersion(4, 2); // Request OpenGL 4.2
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);

    qDebug() << "OpenGL Version:" << format.version();

    // Load the TIFF file
    QString tiffFilePath = "/home/aman/Downloads/Data_Developing3d/Data_Developing3d/DEM.tif";
    rasterLayer = new QgsRasterLayer(tiffFilePath, "TIFF Layer");
    if (!rasterLayer->isValid()) {
        QMessageBox::warning(this, tr("Warning"), tr("Failed to load TIFF file."));
        return;
    } else {
        qDebug() << "TIFF file loaded successfully.";
    }

    // Set up 2D map canvas
    mapCanvas = new QgsMapCanvas(this);
    mapCanvas->setExtent(rasterLayer->extent());
    mapCanvas->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    setCentralWidget(mapCanvas);

    // Set up 3D map settings
    map3DSettings = new Qgs3DMapSettings;
    map3DSettings->setParent(map3DSettings);
    map3DSettings->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    map3DSettings->setCrs(QgsCoordinateReferenceSystem("EPSG:4326"));
    map3DSettings->setExtent(rasterLayer->extent());

    qDebug() << "3D Map Settings CRS:" << map3DSettings->crs().authid();
    qDebug() << "3D Map Extent:" << map3DSettings->extent().toString();

    // Set up terrain generator
    QgsFlatTerrainGenerator *terrainGenerator = new QgsFlatTerrainGenerator;
    map3DSettings->setTerrainGenerator(terrainGenerator);

    // Set up 3D map canvas
    map3DCanvas = new Qgs3DMapCanvas();
    map3DCanvas->setMapSettings(map3DSettings);
    map3DCanvas->resize(800, 600);
    // map3DCanvas->setParent(this); // Ensure the canvas has a parent
    map3DCanvas->show();
    // Add the 3D canvas to a container widget
}
MainWindow::~MainWindow()
{
    delete rasterLayer;
    delete mapCanvas;
    delete map3DSettings;
    delete map3DCanvas;
    delete ui;
}

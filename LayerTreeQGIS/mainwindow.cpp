#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);
    qDebug()<<"window Loaded";


    QgsCoordinateReferenceSystem crs("EPSG:4326");
    QgsProject::instance()->setCrs(crs);

    QString crsUnit = crs.description();  // Get the description of the CRS
    qDebug() << "CRS: " << crsUnit;

    // Create a QGIS layer tree
    QgsLayerTree *layerTree = QgsProject::instance()->layerTreeRoot();
    layerTree->addGroup("Group 1");
    layerTree->addGroup("Group 2");
    layerTree->addGroup("Group 3");


    QgsLayerTreeGroup *group1 = layerTree->findGroup("Group 1");
    QgsLayerTreeGroup *group2 = layerTree->findGroup("Group 2");
    QgsLayerTreeGroup *group3 = layerTree->findGroup("Group 3");

    canvas = DataManager::instance()->mCanvas;

    QgsVectorLayer* baselayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    if (!baselayer->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }

    QgsVectorLayer* layer1 = new QgsVectorLayer("/home/aman/Downloads/shapefiles_toulouse/gis_osm_power_07_1.shp", "Power", "ogr");
    if (!layer1->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }

    QgsVectorLayer* layer2 = new QgsVectorLayer("/home/aman/Downloads/shapefiles_toulouse/gis_osm_roads_07_1.shp", "Road", "ogr");
    if (!layer2->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }

    QgsVectorLayer* layer3 = new QgsVectorLayer("/home/aman/Downloads/shapefiles_toulouse/gis_osm_railways_07_1.shp", "Rail", "ogr");
    if (!layer3->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }

    QgsVectorLayer* layer4 = new QgsVectorLayer("/home/aman/Downloads/shapefiles_toulouse/gis_osm_waterways_07_1.shp", "waterway", "ogr");
    if (!layer4->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }


    group1->addLayer(layer1);
    group2->addLayer(layer2);
    group2->addLayer(layer3);
    group2->addLayer(layer3);
    group3->addLayer(baselayer);
    // this->setProject(QgsProject::instance());
    canvas->setLayers({layer1,layer2,layer3,layer4,baselayer});
    // Set extent of the map to the layer's extent
    canvas->setExtent(baselayer->extent());

    // Show map on the canvas
    canvas->show();


    layertreeview = DataManager::instance()->layertreeview;

    QgsLayerTreeModel *gsmodel = new QgsLayerTreeModel(layerTree);
    layertreeview->setModel(gsmodel);
    CheckBoxItemDelegate *mydel = new CheckBoxItemDelegate();

    // Apply the checkbox delegate to the layer tree view

    // Apply the checkbox delegate to the layer tree view
    // QgsLayerTreeViewItemDelegate *delegate = new QgsLayerTreeViewItemDelegate(layertreeview); // Create the delegate
    // layertreeview->setItemDelegate(delegate); // Set the delegate
    layertreeview->setItemDelegate(mydel);

    ui->verticalLayout->addWidget(layertreeview);
    ui->verticalLayout_2->addWidget(canvas);

}

MainWindow::~MainWindow()
{
    delete ui;
}

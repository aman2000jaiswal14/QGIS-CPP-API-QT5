#include "custommapcanvas.h"
#include <QLabel>
#include <QMap>
#include "qgslayertreegroup.h"
#include "qgslayertreelayer.h"
#include "qgslayertree.h"
#include "qgslayertreeview.h"
#include "qgslayertreemodel.h"
#include <QDir>
#include <memory>
#include "customlayertreemenuprovider.h"
#include "customlayertreeview.h"
CustomMapCanvas::CustomMapCanvas() {
    project = QgsProject::instance();
    QgsCoordinateReferenceSystem crs("EPSG:4326");
    QgsProject::instance()->setCrs(crs);


    // Create a QGIS layer tree
    QgsLayerTree *layerTree = QgsProject::instance()->layerTreeRoot();
    layerTree->addGroup("Group 1");
    layerTree->addGroup("Group 2");


    QgsLayerTreeGroup *group1 = layerTree->findGroup("Group 1");
    QgsLayerTreeGroup *group2 = layerTree->findGroup("Group 2");




    QString crsUnit = crs.description();  // Get the description of the CRS
    qDebug() << "CRS: " << crsUnit;


    QgsVectorLayer* baseLayer = new QgsVectorLayer("/usr/local/share/qgis/resources/data/world_map.gpkg", "World Map", "ogr");
    if (!baseLayer->isValid()) {
        qDebug() << "Layer failed to load!";
        return ;
    }
    QString directoryPath = "/home/aman/Downloads/shapefiles_toulouse";
    QDir dir(directoryPath);

    // Check if the directory exists
    if (!dir.exists()) {
        qDebug() << "Directory does not exist!";
        return;
    }
    QStringList filters;
    filters << "*.shp";  // Filter for .shp files

    // Get a list of all files with .shp extension in the directory
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files);

    QList<QgsMapLayer *>layerlist;
    QList<QgsMapLayer *> layerlist2;
    // Loop through the list and print the file paths
    for (const QFileInfo &fileInfo : fileList) {
        qDebug() << fileInfo.absoluteFilePath();
        QgsVectorLayer* layer1 = new QgsVectorLayer(fileInfo.absoluteFilePath(), fileInfo.fileName(), "ogr");
        if (!layer1->isValid()) {
            qDebug() << "Layer failed to load!";
            return ;
        }
        project->addMapLayer(layer1);
        if(fileInfo.filePath().contains("_a_")) {

            layerlist2.append(layer1);

        }
        else
        {
            layerlist.append(layer1);
            group1->addLayer(layer1);
        }
        // break;

    }
    for(QgsMapLayer *layerinfo : layerlist2)
    {
        layerlist.append(layerinfo);
        group1->addLayer(layerinfo);
    }

    project->addMapLayer(baseLayer);
    layerlist.append(baseLayer);
    group2->addLayer(baseLayer);




    // this->setProject(QgsProject::instance());
    this->setLayers(layerlist);
    // Set extent of the map to the layer's extent
    this->setExtent(baseLayer->extent());

    // Show map on the canvas
    this->show();




    for(QgsMapLayer * mlayer : group1->checkedLayers())
    {
        qDebug()<<mlayer->id();
    }
    for(QgsMapLayer * mlayer : group2->checkedLayers())
    {
        qDebug()<<mlayer->id();
    }


/*// undo visiblity
    qDebug()<<"-----------------------";

    glayer->setItemVisibilityCheckedRecursive(false);
    qDebug()<<group1->isVisible()<<group2->isVisible() <<glayer->isVisible();
    QList<QgsMapLayer *> newLayer;

    for(QgsMapLayer * mlayer : group1->checkedLayers())
    {
        qDebug()<<mlayer->id();
        newLayer.append(mlayer);
    }
    for(QgsMapLayer * mlayer : group2->checkedLayers())
    {
        qDebug()<<mlayer->id();
        newLayer.append(mlayer);
    }


    this->setLayers(newLayer);
*/



    QgsLayerTreeModel *gsmodel = new QgsLayerTreeModel(QgsProject::instance()->layerTreeRoot());

    DataManager::instance()->customLayerTreeView->setModel(gsmodel);
    DataManager::instance()->customLayerTreeView->setCanvas(this);
    // CustomLayerTreeMenuProvider  *customLayerTreeMenuProvider = new CustomLayerTreeMenuProvider;
    // DataManager::instance()->layerTreeViewgs->setMenuProvider(customLayerTreeMenuProvider);

    // QgsLayerTreeViewMenuProvider *menuProvider = DataManager::instance()->layerTreeViewgs->menuProvider();
    // if(menuProvider==nullptr)
    // {
    //     qDebug()<<" menuProvider nullptr";
    // }
    // else
    // {
    //     qDebug()<<"menu created";
    // }
    // QgsLayerTreeViewDefaultActions *defaction =  DataManager::instance()->layerTreeViewgs->defaultActions();
    // if(defaction==nullptr)
    // {
    //     qDebug()<<"defaction nullptr";
    // }
    // else
    // {
    //     qDebug()<<"defaction  created";
    // }
    connect(this, &QgsMapCanvas::xyCoordinates, this, &CustomMapCanvas::xyCoordinateSlot);
    connect(this, &QgsMapCanvas::scaleChanged, this, &CustomMapCanvas::scaleChangedSlot);
}

void CustomMapCanvas::xyCoordinateSlot(QgsPointXY coordinates)
{
    //Convert the coordinates to lat/lon (EPSG:4326)
    QgsCoordinateReferenceSystem crs = project->crs();
    QgsCoordinateTransform transform(crs, QgsCoordinateReferenceSystem("EPSG:4326"), QgsProject::instance());

    QgsPointXY lonLat = transform.transform(coordinates);
    double latitude = lonLat.y();
    double longitude = lonLat.x();

    // Update the label with the coordinates
    emit xyCoordinatesSignal(lonLat);
}

void CustomMapCanvas::scaleChangedSlot(double scale)
{
    emit scaleLabelSignal(scale);
}

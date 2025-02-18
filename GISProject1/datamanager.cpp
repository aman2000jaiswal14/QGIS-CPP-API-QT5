#include "datamanager.h"

DataManager *DataManager::instance()
{
    static DataManager* instance = nullptr;
    if (!instance) {
        instance = new DataManager();
    }
    return instance;
}

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    layerTreeViewgs = new QgsLayerTreeView;
    customLayerTreeView = new CustomLayerTreeView;




}

DataManager::~DataManager()
{

}

void DataManager::nameslot()
{

}

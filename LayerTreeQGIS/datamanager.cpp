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
    layertreeview = new QgsLayerTreeView;
    mCanvas = new QgsMapCanvas;

}

DataManager::~DataManager()
{

}

void DataManager::nameslot()
{

}

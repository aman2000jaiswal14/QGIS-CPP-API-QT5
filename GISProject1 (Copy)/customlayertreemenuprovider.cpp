#include "customlayertreemenuprovider.h"
#include <QObject>  // Include QObject here too for the connect mechanism

CustomLayerTreeMenuProvider::CustomLayerTreeMenuProvider() {

}

QMenu *CustomLayerTreeMenuProvider::createContextMenu()
{
    QMenu *menu = new QMenu;
    menu->addAction("name",this,SLOT(nameFunSlot()));

    qDebug()<<"create Menu called";
    return menu;
}

CustomLayerTreeMenuProvider::~CustomLayerTreeMenuProvider()
{
    // delete menu;
}


void CustomLayerTreeMenuProvider::nameFunSlot()
{
    qDebug() << "name";
    qDebug()<<"menu selected : "<<DataManager::instance()->layerTreeViewgs->currentLayer()->id();


}

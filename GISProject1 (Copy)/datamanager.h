#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDebug>
#include "qgslayertreegroup.h"
#include "qgslayertreelayer.h"
#include "qgslayertree.h"
#include "qgslayertreeview.h"
#include "customlayertreeview.h"

class DataManager : public QObject
{
    Q_OBJECT

public:
    // Delete the copy constructor and assignment operator to prevent copies
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    // Static method to access the single instance
    static DataManager* instance();

private:

    // Private constructor to prevent instantiation
    DataManager(QObject* parent = nullptr);
    // Private destructor to allow safe deletion
    ~DataManager();


public:
    CustomLayerTreeView *customLayerTreeView;
    QgsLayerTreeView *layerTreeViewgs;

    QMenu *menu;

public slots:
    void nameslot();

};

#endif // DATAMANAGER_H

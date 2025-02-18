#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include "qgslayertreeview.h"
#include "qgsmapcanvas.h"
class DataManager : public QObject
{
    Q_OBJECT

public:
    // Delete the copy constructor and assignment operator to prevent copies
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    // Static method to access the single instance
    static DataManager* instance();

    QgsLayerTreeView *layertreeview ;
    QgsMapCanvas *mCanvas;
private:

    // Private constructor to prevent instantiation
    DataManager(QObject* parent = nullptr);
    // Private destructor to allow safe deletion
    ~DataManager();


public:


public slots:
    void nameslot();

};

#endif // DATAMANAGER_H

#ifndef CUSTOMMAPCANVAS_H
#define CUSTOMMAPCANVAS_H

#include <QObject>
#include <QWidget>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include "datamanager.h"
#include <QMenu>
#include <QAction>
#include "qgslayertreegroup.h"
#include "qgslayertreelayer.h"
#include "qgslayertree.h"
#include "qgslayertreeview.h"
#include "qgslayertreemodel.h"
#include <QDir>
#include <memory>
#include "customlayertreemenuprovider.h"
#include "customlayertreeview.h"
#include "qgscheckablecombobox.h"
class CustomMapCanvas : public QgsMapCanvas
{
    Q_OBJECT


public:
    CustomMapCanvas();



private :
    QgsProject *project;
public slots:
    void xyCoordinateSlot(QgsPointXY);
    void scaleChangedSlot(double scale);
signals:
    void xyCoordinatesSignal(QgsPointXY);
    void scaleLabelSignal(double scale);

};


#include <QCheckBox>
#include <QVariant>
#include <QDebug>

class CheckableLayerTreeModel : public QgsLayerTreeModel
{
    Q_OBJECT

public:
    explicit CheckableLayerTreeModel(QgsLayerTree *rootNode, QObject *parent = nullptr)
        : QgsLayerTreeModel(rootNode, parent)
    {
        // Initialization if necessary
    }

    // Override data() to handle the check state
    QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
            return QVariant();

        // Handle the Qt::CheckStateRole for checkable items
        // if (role == Qt::CheckStateRole) {
        //     // Check if the item is checked or not
        //     QgsMapLayer *layer = static_cast<QgsLayerTreeNode*>(index.internalPointer())->layer();
        //     if (layer) {
        //         // If the layer is checked, return Qt::Checked, otherwise Qt::Unchecked
        //         return layer->isVisible() ? Qt::Checked : Qt::Unchecked;
        //     }
        // }

        return QgsLayerTreeModel::data(index, role);  // Call the base class method for other roles
    }

    // Override setData() to handle changes to the check state
    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        // if (role == Qt::CheckStateRole) {
        //     QgsLayerTreeNode *node = static_cast<QgsLayerTreeNode*>(index.internalPointer());
        //     if (node) {
        //         QgsMapLayer *layer = node->layer();
        //         if (layer) {
        //             bool checked = (value == Qt::Checked);
        //             layer->setVisible(checked);  // Set the layer's visibility based on the checked state
        //             emit dataChanged(index, index, { Qt::CheckStateRole });
        //             return   true;
        //         }
        //     }
        // }

        // return QgsLayerTreeModel::setData(index, value, role);  // Call the base class method for other roles
    }

    // Optionally, implement the flags() method to indicate the item is checkable
    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        Qt::ItemFlags flags = QgsLayerTreeModel::flags(index);
        if (index.isValid()) {
            // Make the item checkable
            flags |= Qt::ItemIsUserCheckable;
        }
        return flags;
    }
};


#endif // CUSTOMMAPCANVAS_H

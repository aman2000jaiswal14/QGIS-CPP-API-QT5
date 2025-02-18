#ifndef CUSTOMLAYERTREEVIEW_H
#define CUSTOMLAYERTREEVIEW_H

#include "qgslayertreegroup.h"
#include "qgslayertreelayer.h"
#include "qgslayertree.h"
#include "qgslayertreeview.h"
#include "qgslayertreemodel.h"
#include "qgsmapcanvas.h"
#include <QMenu>
class CustomLayerTreeView : public QgsLayerTreeView
{
    Q_OBJECT

public:
    explicit CustomLayerTreeView(QWidget *parent = nullptr)
        : QgsLayerTreeView(parent)
    {}
    void setCanvas(QgsMapCanvas *mcanvas){
        m_canvas = mcanvas;
    }
protected:

    void contextMenuEvent(QContextMenuEvent *event) override
    {
    //     // Get the layer under the cursor
        QgsMapLayer *layer = this->currentLayer();

         QgsLayerTreeGroup *gpnode = this->currentGroupNode();

        if (layer)
        {
            // Create the context menu
            QMenu menu(this);

            // Create the "Zoom to Layer" action
            QAction *zoomAction = new QAction("Zoom to Layer", this);
            menu.addAction(zoomAction);

            QAction *hideAction = new QAction("Hide Layer", this);
            menu.addAction(hideAction);

            //Connect the action to the zoom function
            connect(zoomAction, &QAction::triggered, this, [this, layer]() {
                zoomToLayer(layer);
            });
            connect(hideAction, &QAction::triggered, this, [this, layer]() {
                hideLayer(layer);
            });

            // Execute the menu
            menu.exec(event->globalPos());
        }
        else if(gpnode)
        {
            QMenu menu(this);

            // Create the "Zoom to Layer" action
            QAction *hideAction = new QAction("Hide Layer", this);
            menu.addAction(hideAction);
            connect(hideAction, &QAction::triggered, this, [this, layer]() {
                hideLayer(layer);
            });
            menu.exec(event->globalPos());

        }
    }

private slots:
    void zoomToLayer(QgsMapLayer *layer)
    {
        QgsMapCanvas *canvas = m_canvas;
        if (canvas && layer)
        {
            // Get the layer's extent
            QgsRectangle extent = layer->extent();

            // Zoom to the layer's extent
            canvas->setExtent(extent);
            canvas->refresh();
        }
    }
    void hideLayer(QgsMapLayer *layer)
    {
        QgsLayerTree *layerTree = QgsProject::instance()->layerTreeRoot();
        QgsMapCanvas *canvas = m_canvas;

        if (!layer) {
            // Handle group visibility (if no specific layer is selected)
            QgsLayerTreeGroup *group = this->currentGroupNode();

            if (group) {
                bool isVisible = group->isItemVisibilityCheckedRecursive();
                group->setItemVisibilityCheckedRecursive(!isVisible);  // Toggle visibility of group

                // Loop through the group's child nodes and hide/show them
                QList<QgsLayerTreeNode *> childNodes = group->children();
                for (QgsLayerTreeNode *childNode : childNodes) {
                    if (QgsLayerTreeLayer *layerNode = dynamic_cast<QgsLayerTreeLayer *>(childNode)) {
                        // Only toggle visibility if it's a layer node
                        layerNode->setItemVisibilityCheckedRecursive(!isVisible);  // Toggle visibility of each layer
                    }
                }
            }
        } else {
            // Handle individual layer visibility (if a specific layer is selected)
            this->currentNode()->setItemVisibilityCheckedRecursive(!this->currentNode()->isItemVisibilityCheckedRecursive());


        }

        // Get all checked layers
        QList<QgsMapLayer *> checkedLayers;
        for (QgsMapLayer *mlayer : layerTree->checkedLayers()) {
            qDebug()<<mlayer->id();
            checkedLayers.append(mlayer);
        }

        // Update the canvas with the checked layers
        m_canvas->setLayers(checkedLayers);

        // Refresh the canvas to reflect visibility changes
        canvas->refresh();
    }


private:
    QgsMapCanvas *m_canvas;
};
#endif

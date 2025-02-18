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
    explicit CustomLayerTreeView(QWidget *parent = nullptr);
    void setCanvas(QgsMapCanvas *mcanvas);
protected:

    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void zoomToLayer(QgsMapLayer *layer);
    void hideLayer(QgsMapLayer *layer);


private:
    QgsMapCanvas *m_canvas;
};
#endif

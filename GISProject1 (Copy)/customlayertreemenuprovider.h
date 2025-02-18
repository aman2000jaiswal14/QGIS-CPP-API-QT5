#ifndef CUSTOMLAYERTREEMENUPROVIDER_H
#define CUSTOMLAYERTREEMENUPROVIDER_H

#include <QObject>  // Ensure QObject is included for meta-object system features
#include <QMenu>
#include <QAction>
#include <qgslayertreeview.h>
#include <QDebug>
#include "datamanager.h"

class CustomLayerTreeMenuProvider : public QObject, public QgsLayerTreeViewMenuProvider
{

    Q_OBJECT

public:
    CustomLayerTreeMenuProvider();
    QMenu *createContextMenu() override;
    ~CustomLayerTreeMenuProvider();
private slots:
    void nameFunSlot();
};
#endif // CUSTOMLAYERTREEMENUPROVIDER_H

// Now, in your main function or the appropriate context:

#ifndef CUSTOMMAPCANVAS_H
#define CUSTOMMAPCANVAS_H

#include <QObject>
#include "qgsmapcanvas.h"
#include "qgspointxy.h"
#include <QMenu>
#include <QInputDialog>

class CustomMapCanvas : public QgsMapCanvas {
    Q_OBJECT

public:
    explicit CustomMapCanvas(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void onOpen(const QgsFeature& feature);
    void onClose(const QgsFeature& feature);

};
#endif // CUSTOMMAPCANVAS_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgsrasterlayer.h"
#include "qgsmapcanvas.h"
#include "qgs3d.h"
#include "qgs3dmapcanvas.h"
#include "qgs3dmapsettings.h"
#include <QGuiApplication>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DCore/QTransform>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QgsRasterLayer *rasterLayer;
    QgsMapCanvas *mapCanvas;
    Qgs3DMapSettings *map3DSettings;
    Qgs3DMapCanvas *map3DCanvas;
};
#endif // MAINWINDOW_H

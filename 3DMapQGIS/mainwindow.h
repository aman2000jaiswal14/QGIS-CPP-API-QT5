#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgsapplication.h>
#include <qgsmapcanvas.h>
#include <qgs3dmapcanvas.h>
#include <qgsproject.h>
#include <qgsvectorlayer.h>
#include <qgs3dmapsettings.h>
#include <qgs3dmapscene.h>
#include <QVBoxLayout>
#include <qgsrasterlayer.h>
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

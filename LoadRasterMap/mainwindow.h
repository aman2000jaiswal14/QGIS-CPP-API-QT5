#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qgis_core.h"
#include "qgis_gui.h"
#include "qgsapplication.h"
#include "qgsrasterlayer.h"
#include "qgsvectorlayer.h"
#include "qgsvectorlayer.h"
#include "qgis.h"
#include "qgsmapcanvas.h"
#include <QMessageBox>
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

    QLabel *imageLabel;  // QLabel to display image
    QgsRasterLayer *rasterLayer;
    QgsMapCanvas *canvas;

    void loadImage(const QString &filePath);
};
#endif // MAINWINDOW_H

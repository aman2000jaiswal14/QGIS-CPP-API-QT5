#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QToolButton>
#include <QPushButton>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyle>
#include "qgspointxy.h"
#include <QTreeView>
#include "datamanager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class ConstDef;
class CustomMapCanvas;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void menuBarWidgets();

public slots:
    void canvasXYCoordinatesSlot(QgsPointXY coordinates);
    void canvasScaleLabelSlot(double scale);
private slots:




    void on_closeButton_clicked();


private:
    Ui::MainWindow *ui;

    // CustomCanvas
    CustomMapCanvas *canvas;

    //Menu Bar Widgets
    QToolButton *closebtn;
    QHBoxLayout *menuFrameLayout;



};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ConstDef.h>
#include <custommapcanvas.h>
#include "QStandardItemModel"
#include "qgslayertreeview.h"
#include "qgslayertreemodel.h"
#include "qgslayertreeviewitemdelegate.h"
#include "qgslayertreeviewdefaultactions.h"
#include "qgslayertreeviewindicator.h"
#include "customlayertreeview.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);
    qDebug()<<"window Loaded";

    // Loading widgets
    menuBarWidgets();

    // -- Loading widgets

    // Canvas
    canvas = new CustomMapCanvas;

    ui->centralLayout->addWidget(canvas);

    connect(canvas,&CustomMapCanvas::xyCoordinatesSignal,this,&MainWindow::canvasXYCoordinatesSlot);
    connect(canvas,&CustomMapCanvas::scaleLabelSignal,this,&MainWindow::canvasScaleLabelSlot);
    // -- Canvas


    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    ui->leftPanelFrame->setLayout(leftPanelLayout);


    /*
    QTreeView *layerTreeView = new QTreeView;


    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *rootItem = model->invisibleRootItem();

    // Add the groups to the model
    QStandardItem *groupItem1 = new QStandardItem("Group 1");
    rootItem->appendRow(groupItem1);

    QStandardItem *layerItem11 = new QStandardItem("World Map");
    groupItem1->appendRow(layerItem11);

    QStandardItem *groupItem2 = new QStandardItem("Group 2");
    rootItem->appendRow(groupItem2);
    QStandardItem *layerItem21 = new QStandardItem("Toulouse Roads");
    groupItem2->appendRow(layerItem21);

    QStandardItem *layerItem22 = new QStandardItem("Toulouse Rail");
    groupItem2->appendRow(layerItem22);

    groupItem1->setCheckable(true);
    layerItem11->setCheckable(true);
    groupItem2->setCheckable(true);
    layerItem21->setCheckable(true);
    layerItem22->setCheckable(true);


    layerTreeView->setModel(model);
    */



    leftPanelLayout->addWidget(DataManager::instance()->customLayerTreeView);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuBarWidgets()
{

    QIcon closeIcon(QString("%1/close.png").arg(ICON_PATH));

    ui->closeButton->setIcon(closeIcon);
    ui->closeButton->setIconSize(QSize(24, 24));
    ui->closeButton->setStyleSheet("border: none;");






}

void MainWindow::canvasXYCoordinatesSlot(QgsPointXY coordinates)
{
    // QgsCoordinateReferenceSystem crs = mapLayer->crs();
    // QgsCoordinateTransform transform(crs, QgsCoordinateReferenceSystem("EPSG:4326"), QgsProject::instance());

    QgsPointXY lonLat = coordinates;//transform.transform(coordinates);
    double latitude = lonLat.y();
    double longitude = lonLat.x();

    // Update the label with the coordinates
    ui->latLabel->setText(QString::number(latitude));
    ui->lonLabel->setText(QString::number(longitude));
}

void MainWindow::canvasScaleLabelSlot(double scale)
{
    ui->scaleLabel->setText(QString::number(scale));
}


void MainWindow::on_closeButton_clicked()
{

    ::exit(1);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = new CustomMapCanvas();
    setCentralWidget(canvas);


}

MainWindow::~MainWindow()
{
    delete ui;
}

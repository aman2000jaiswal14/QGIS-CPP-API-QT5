#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <custommapcanvas.h>
#include <qgsrasterlayer.h>
#include <qgsvectorlayer.h>
#include <QDebug>

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
    CustomMapCanvas *canvas;
};
#endif // MAINWINDOW_H

#include "cameramatriceswidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _cameraMatricesWidget = new CameraMatricesWidget;

    this->setCentralWidget(_cameraMatricesWidget);
}

MainWindow::~MainWindow()
{

}

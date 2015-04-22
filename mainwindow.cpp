#include <QVboxLayout>
#include <QWidget>

#include "cameramatriceswidget.h"
#include "extrinsiccontrolwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _cameraMatricesWidget = new CameraMatricesWidget;
    _extrinsicControlWidget = new ExtrinsicControlWidget;

    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(_cameraMatricesWidget);
    layout->addWidget(_extrinsicControlWidget);
    widget->setLayout(layout);

    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

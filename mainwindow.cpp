#include <QTabWidget>
#include <QVboxLayout>
#include <QWidget>

#include "camera.h"
#include "cameramatriceswidget.h"
#include "extrinsiccontrolwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _camera(nullptr)
{
    _camera = new Camera;

    _cameraMatricesWidget = new CameraMatricesWidget(_camera);
    _extrinsicControlWidget = new ExtrinsicControlWidget(_camera);

    QWidget* widget = new QWidget;

    QTabWidget* tabs = new QTabWidget;
    tabs->addTab(_extrinsicControlWidget, "Extrinsic");

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(_cameraMatricesWidget);
    layout->addWidget(tabs);
    widget->setLayout(layout);

    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    if (_camera) delete _camera;
}

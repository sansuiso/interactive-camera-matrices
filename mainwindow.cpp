#include <QVboxLayout>
#include <QWidget>

#include "cameramatriceswidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _cameraMatricesWidget = new CameraMatricesWidget;

    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(_cameraMatricesWidget);
    widget->setLayout(layout);

    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

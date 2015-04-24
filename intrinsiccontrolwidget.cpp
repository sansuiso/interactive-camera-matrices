#include <QApplication>
#include <QVBoxLayout>

#include "camera.h"
#include "intrinsiccontrolwidget.h"
#include "slidingcontrolwidget.h"

IntrinsicControlWidget::IntrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto identity = [](int value) ->float {
        return (float)value;
    };

    _focalWidget = new SlidingControlWidget("Focal length (mm):", 1, 35, (int)camera->FNumber(), identity);
    connect(_focalWidget, &SlidingControlWidget::valueChanged, this, &IntrinsicControlWidget::updateCamera);
    layout->addWidget(_focalWidget);

    _pixelSizeWidget = new SlidingControlWidget("Pixel size (um):", 0, 100, (int)camera->micronsPerPixel() - 1.0,
                                                [](int value) { return 1.0f + 0.1f*value;});
    connect(_pixelSizeWidget, &SlidingControlWidget::valueChanged, this, &IntrinsicControlWidget::updateCamera);
    layout->addWidget(_pixelSizeWidget);

    _skewWidget = new SlidingControlWidget("Skew:", 0, 100, camera->skew(),
                                                [](int value) { return 3.0f*value;});
    connect(_skewWidget, &SlidingControlWidget::valueChanged, this, &IntrinsicControlWidget::updateCamera);
    layout->addWidget(_skewWidget);

    this->setLayout(layout);
}

IntrinsicControlWidget::~IntrinsicControlWidget()
{

}

void IntrinsicControlWidget::updateCamera()
{
    if (_camera)
    {
        _camera->setFocalLength(_focalWidget->value());
        _camera->setMicronsPerPixel(_pixelSizeWidget->value());
        _camera->setSkew(_skewWidget->value());

        QApplication::activeWindow()->update();
    }
}

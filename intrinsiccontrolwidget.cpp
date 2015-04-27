#include <QVBoxLayout>

#include "camera.h"
#include "cameramatriceswidget.h"
#include "intrinsiccontrolwidget.h"
#include "slidingcontrolwidget.h"

IntrinsicControlWidget::IntrinsicControlWidget(Camera *camera, CameraMatricesWidget *cameraViewWidget, QWidget *parent)
    : QWidget(parent), _camera(camera), _cameraViewWidget(cameraViewWidget)
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

    _aspectRatioWidget = new SlidingControlWidget("Aspect ratio:", -50, 50,
                                                  (int)(0.02*(camera->aspectRatio() - 1.0f)),
                                                  [](int value) { return 1.0f + 0.02f*value; });
    connect(_aspectRatioWidget, &SlidingControlWidget::valueChanged, this, &IntrinsicControlWidget::updateCamera);
    layout->addWidget(_aspectRatioWidget);

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
        _camera->setAspectRatio(_aspectRatioWidget->value());

        if (_cameraViewWidget) {
            _cameraViewWidget->update();
        }
    }
}

#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

#include "camera.h"
#include "cameramatriceswidget.h"
#include "intrinsiccontrolwidget.h"
#include "intrinsicmatrixmodel.h"
#include "slidingcontrolwidget.h"

IntrinsicControlWidget::IntrinsicControlWidget(Camera *camera, CameraMatricesWidget *cameraViewWidget, QWidget *parent)
    : QWidget(parent), _camera(camera), _cameraViewWidget(cameraViewWidget)
{
    QHBoxLayout* box = new QHBoxLayout;
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

    _intrinsicMatrixModel = new IntrinsicMatrixModel(_camera);
    connect(this, &IntrinsicControlWidget::cameraWasUpdated, _intrinsicMatrixModel,
            &IntrinsicMatrixModel::handleCameraUpdate);

    QTableView* tableView = new QTableView;
    tableView->horizontalHeader()->hide();
    tableView->setModel(_intrinsicMatrixModel);

    box->addLayout(layout);
    box->addWidget(tableView);

    this->setLayout(box);
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

        emit cameraWasUpdated();

        if (_cameraViewWidget) {
            _cameraViewWidget->update();
        }
    }
}

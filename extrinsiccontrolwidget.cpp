#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QString>
#include <QTableView>
#include <QVBoxLayout>

#include "camera.h"
#include "cameramatriceswidget.h"
#include "extrinsiccontrolwidget.h"
#include "extrinsicmatrixmodel.h"
#include "slidingcontrolwidget.h"

int const ExtrinsicControlWidget::SLIDER_STEPS = 200;

ExtrinsicControlWidget::ExtrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QHBoxLayout* box = new QHBoxLayout;
    QVBoxLayout* boxPosition = new QVBoxLayout;
    QVBoxLayout* boxAngles = new QVBoxLayout;

    auto positionMapping = [](int sliderValue) -> float {
        return 10.0f * sliderValue / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    };

    auto angleMapping = [](int sliderValue) -> float {
        return 45.0f * sliderValue / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    };

    _xSlidingWidget = new SlidingControlWidget("X:",
                                               -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                               0, positionMapping);
    boxPosition->addWidget(_xSlidingWidget);
    connect(_xSlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    _ySlidingWidget = new SlidingControlWidget("Y:",
                                               -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                               0, positionMapping);
    boxPosition->addWidget(_ySlidingWidget);
    connect(_ySlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    _zSlidingWidget = new SlidingControlWidget("Z:",
                                               -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                               0, positionMapping);
    boxPosition->addWidget(_zSlidingWidget);
    connect(_zSlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    _thetaXSlidingWidget = new SlidingControlWidget(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("x"),
                                                    -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                                    0, angleMapping);
    boxAngles->addWidget(_thetaXSlidingWidget);
    connect(_thetaXSlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    _thetaYSlidingWidget = new SlidingControlWidget(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("y"),
                                                    -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                                    0, angleMapping);
    boxAngles->addWidget(_thetaYSlidingWidget);
    connect(_thetaYSlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    _thetaZSlidingWidget = new SlidingControlWidget(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("z"),
                                                    -ExtrinsicControlWidget::SLIDER_STEPS, ExtrinsicControlWidget::SLIDER_STEPS,
                                                    0, angleMapping);
    boxAngles->addWidget(_thetaZSlidingWidget);
    connect(_thetaZSlidingWidget, &SlidingControlWidget::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);

    box->addLayout(boxPosition);
    box->addLayout(boxAngles);

    _extrinsincMatrixModel = new ExtrinsicMatrixModel(_camera);
    connect(this, &ExtrinsicControlWidget::cameraWasUpdated,
            _extrinsincMatrixModel, &ExtrinsicMatrixModel::handleCameraUpdate);

    QTableView* tableView = new QTableView;
    tableView->setModel(_extrinsincMatrixModel);
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->hide();

    box->addWidget((tableView));

    this->setLayout(box);
}

ExtrinsicControlWidget::~ExtrinsicControlWidget()
{

}

void ExtrinsicControlWidget::updateCameraPosition()
{
    if (_camera)
    {
        float x = _xSlidingWidget->value();
        float y = _ySlidingWidget->value();
        float z = _zSlidingWidget->value();

        float thetaX = _thetaXSlidingWidget->value();
        float thetaY = _thetaYSlidingWidget->value();
        float thetaZ = _thetaZSlidingWidget->value();

        _camera->setWorldPosition(x, y, z);
        _camera->setWorldOrientation(thetaX, thetaY, thetaZ);

        emit cameraWasUpdated();
    }
}

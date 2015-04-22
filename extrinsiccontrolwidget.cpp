#include <QDebug>
#include <QSlider>
#include <QVBoxLayout>

#include "camera.h"
#include "extrinsiccontrolwidget.h"

int const ExtrinsicControlWidget::SLIDER_STEPS = 200;

ExtrinsicControlWidget::ExtrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto setupSlider = [&](QSlider* slider) {
        slider->setMinimum(-ExtrinsicControlWidget::SLIDER_STEPS);
        slider->setMaximum(ExtrinsicControlWidget::SLIDER_STEPS);
        layout->addWidget(slider);

        connect(slider, &QSlider::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);
    };

    _xSlider = new QSlider(Qt::Horizontal);
    _ySlider = new QSlider(Qt::Horizontal);
    _zSlider = new QSlider(Qt::Horizontal);

    _thetaXSlider = new QSlider(Qt::Horizontal);
    _thetaYSlider = new QSlider(Qt::Horizontal);
    _thetaZSlider = new QSlider(Qt::Horizontal);

    setupSlider(_xSlider);
    setupSlider(_ySlider);
    setupSlider(_zSlider);

    setupSlider(_thetaXSlider);
    setupSlider(_thetaYSlider);
    setupSlider(_thetaZSlider);

    this->setLayout(layout);
}

ExtrinsicControlWidget::~ExtrinsicControlWidget()
{

}

void ExtrinsicControlWidget::updateCameraPosition()
{
    qDebug() << __FUNCTION__;

    float x = 10.0f * _xSlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    float y = 10.0f * _ySlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    float z = 10.0f * _zSlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;

    float thetaX = 45.0f *_thetaXSlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    float thetaY = 45.0f *_thetaYSlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;
    float thetaZ = 45.0f *_thetaZSlider->value() / (float)ExtrinsicControlWidget::SLIDER_STEPS;

    if (_camera)
    {
        _camera->setWorldPosition(x, y, z);
        _camera->setWorldOrientation(thetaX, thetaY, thetaZ);

        this->parentWidget()->update();
    }
}

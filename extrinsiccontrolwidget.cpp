#include <QDebug>
#include <QSlider>
#include <QVBoxLayout>

#include "camera.h"
#include "extrinsiccontrolwidget.h"

ExtrinsicControlWidget::ExtrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto setupSlider = [&](QSlider* slider) {
        slider->setMinimum(-200);
        slider->setMaximum(200);
        layout->addWidget(slider);

        connect(slider, &QSlider::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);
    };

    _xSlider = new QSlider(Qt::Horizontal);
    _ySlider = new QSlider(Qt::Horizontal);
    _zSlider = new QSlider(Qt::Horizontal);

    setupSlider(_xSlider);
    setupSlider(_ySlider);
    setupSlider(_zSlider);

    this->setLayout(layout);
}

ExtrinsicControlWidget::~ExtrinsicControlWidget()
{

}

void ExtrinsicControlWidget::updateCameraPosition()
{
    qDebug() << __FUNCTION__;

    float x = 0.05*_xSlider->value();
    float y = 0.05*_ySlider->value();
    float z = 0.05*_zSlider->value();

    if (_camera) {
        _camera->setWorldPosition(x, y, z);
        this->parentWidget()->update();
    }
}

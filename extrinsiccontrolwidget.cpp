#include <QSlider>
#include <QVBoxLayout>

#include "camera.h"
#include "extrinsiccontrolwidget.h"

ExtrinsicControlWidget::ExtrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto setupSlider = [&](QSlider* slider) {
        slider->setMinimum(-10);
        slider->setMaximum(10);
        layout->addWidget(slider);
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


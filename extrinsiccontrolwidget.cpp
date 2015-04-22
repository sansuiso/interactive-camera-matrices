#include <QSlider>
#include <QVBoxLayout>

#include "extrinsiccontrolwidget.h"

ExtrinsicControlWidget::ExtrinsicControlWidget(QWidget *parent) : QWidget(parent)
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


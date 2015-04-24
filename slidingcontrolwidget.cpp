#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

#include "slidingcontrolwidget.h"

SlidingControlWidget::SlidingControlWidget(const QString &title, int minSliderValue, int maxSliderValue, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;

    QLabel *titleLabel = new QLabel(title);
    layout->addWidget(titleLabel);

    _valueLabel = new QLabel("VAL");
    layout->addWidget((_valueLabel));

    _slider = new QSlider(Qt::Horizontal);
    _slider->setMinimum(minSliderValue);
    _slider->setMaximum(maxSliderValue);
    layout->addWidget(_slider);

    this->setLayout(layout);
}

SlidingControlWidget::~SlidingControlWidget()
{

}


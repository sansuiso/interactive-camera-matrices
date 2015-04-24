#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

#include "slidingcontrolwidget.h"

SlidingControlWidget::SlidingControlWidget(const QString &title,
                                           int minSliderValue, int maxSliderValue, int initialValue,
                                           std::function<float(int)> mapping, QWidget *parent)
    : QWidget(parent), _mapping(mapping)
{
    QHBoxLayout *layout = new QHBoxLayout;

    QLabel *titleLabel = new QLabel(title);
    layout->addWidget(titleLabel);

    _valueLabel = new QLabel("VAL");
    layout->addWidget((_valueLabel));

    _slider = new QSlider(Qt::Horizontal);
    _slider->setMinimum(minSliderValue);
    _slider->setMaximum(maxSliderValue);
    _slider->setValue(initialValue);
    layout->addWidget(_slider);

    connect(_slider, &QSlider::valueChanged, this,
            [&](int value) {
        setValue(_mapping(value));
        emit valueChanged(_value);
    });

    this->setValue(_mapping(initialValue));

    this->setLayout(layout);
}

SlidingControlWidget::~SlidingControlWidget()
{

}

void SlidingControlWidget::setValue(float value)
{
    _value = value;
    _valueLabel->setText(QString("%1").arg(_value));
}

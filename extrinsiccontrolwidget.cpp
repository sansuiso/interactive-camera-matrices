#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QString>
#include <QVBoxLayout>

#include "camera.h"
#include "extrinsiccontrolwidget.h"

int const ExtrinsicControlWidget::SLIDER_STEPS = 200;

ExtrinsicControlWidget::ExtrinsicControlWidget(Camera *camera, QWidget *parent)
    : QWidget(parent), _camera(camera)
{
    QHBoxLayout* box = new QHBoxLayout;
    QVBoxLayout* boxPosition = new QVBoxLayout;
    QVBoxLayout* boxAngles = new QVBoxLayout;

    auto setupSlider = [&](QString const& text, QSlider* slider, QVBoxLayout* layout) {
        QHBoxLayout* hbox = new QHBoxLayout;

        QLabel* label = new QLabel(text);
        hbox->addWidget(label);

        slider->setMinimum(-ExtrinsicControlWidget::SLIDER_STEPS);
        slider->setMaximum(ExtrinsicControlWidget::SLIDER_STEPS);
        hbox->addWidget(slider);

        layout->addLayout(hbox);

        connect(slider, &QSlider::valueChanged, this, &ExtrinsicControlWidget::updateCameraPosition);
    };

    _xSlider = new QSlider(Qt::Horizontal);
    _ySlider = new QSlider(Qt::Horizontal);
    _zSlider = new QSlider(Qt::Horizontal);

    _thetaXSlider = new QSlider(Qt::Horizontal);
    _thetaYSlider = new QSlider(Qt::Horizontal);
    _thetaZSlider = new QSlider(Qt::Horizontal);

    setupSlider("X", _xSlider, boxPosition);
    setupSlider("Y", _ySlider, boxPosition);
    setupSlider("Z", _zSlider, boxPosition);

    setupSlider(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("x"), _thetaXSlider, boxAngles);
    setupSlider(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("x"), _thetaYSlider, boxAngles);
    setupSlider(QString("%1_%2").arg(QChar(0xf4, 0x03)).arg("x"), _thetaZSlider, boxAngles);

    box->addLayout(boxPosition);
    box->addLayout(boxAngles);
    this->setLayout(box);
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

        QApplication::activeWindow()->update();
    }
}

#ifndef EXTRINSICCONTROLWIDGET_H
#define EXTRINSICCONTROLWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(QSlider)

class ExtrinsicControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExtrinsicControlWidget(Camera* camera, QWidget *parent = 0);
    ~ExtrinsicControlWidget();

signals:

public slots:

private:
    Camera* _camera;

    static int const SLIDER_STEPS;

    QSlider* _xSlider;
    QSlider* _ySlider;
    QSlider* _zSlider;

    QSlider* _thetaXSlider;
    QSlider* _thetaYSlider;
    QSlider* _thetaZSlider;

    void updateCameraPosition();
};

#endif // EXTRINSICCONTROLWIDGET_H

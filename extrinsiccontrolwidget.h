#ifndef EXTRINSICCONTROLWIDGET_H
#define EXTRINSICCONTROLWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(SlidingControlWidget)

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

    SlidingControlWidget* _xSlidingWidget;
    SlidingControlWidget* _ySlidingWidget;
    SlidingControlWidget* _zSlidingWidget;

    SlidingControlWidget* _thetaXSlidingWidget;
    SlidingControlWidget* _thetaYSlidingWidget;
    SlidingControlWidget* _thetaZSlidingWidget;

    void updateCameraPosition();
};

#endif // EXTRINSICCONTROLWIDGET_H

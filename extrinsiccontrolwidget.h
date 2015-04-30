#ifndef EXTRINSICCONTROLWIDGET_H
#define EXTRINSICCONTROLWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(CameraMatricesWidget)
QT_FORWARD_DECLARE_CLASS(ExtrinsicMatrixModel)
QT_FORWARD_DECLARE_CLASS(SlidingControlWidget)

class ExtrinsicControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExtrinsicControlWidget(Camera* camera, QWidget *parent = 0);
    ~ExtrinsicControlWidget();

signals:
    void cameraWasUpdated();

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

    ExtrinsicMatrixModel* _extrinsincMatrixModel;

    void updateCameraPosition();
};

#endif // EXTRINSICCONTROLWIDGET_H

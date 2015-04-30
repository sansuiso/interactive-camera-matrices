#ifndef INTRINSICCONTROLWIDGET_H
#define INTRINSICCONTROLWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(CameraMatricesWidget)
QT_FORWARD_DECLARE_CLASS(IntrinsicMatrixModel)
QT_FORWARD_DECLARE_CLASS(SlidingControlWidget)

class IntrinsicControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntrinsicControlWidget(Camera* camera, QWidget *parent = 0);
    ~IntrinsicControlWidget();

signals:
    void cameraWasUpdated();

public slots:
    void updateCamera();

private:
    Camera* _camera;

    SlidingControlWidget* _focalWidget;
    SlidingControlWidget* _pixelSizeWidget;
    SlidingControlWidget* _skewWidget;
    SlidingControlWidget* _aspectRatioWidget;

    IntrinsicMatrixModel* _intrinsicMatrixModel;
};

#endif // INTRINSICCONTROLWIDGET_H

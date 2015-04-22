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

    QSlider* _xSlider;
    QSlider* _ySlider;
    QSlider* _zSlider;
};

#endif // EXTRINSICCONTROLWIDGET_H

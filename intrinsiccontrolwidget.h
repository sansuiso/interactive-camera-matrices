#ifndef INTRINSICCONTROLWIDGET_H
#define INTRINSICCONTROLWIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(Camera)

class IntrinsicControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntrinsicControlWidget(Camera* camera, QWidget *parent = 0);
    ~IntrinsicControlWidget();

signals:

public slots:

private:
    Camera* _camera;
};

#endif // INTRINSICCONTROLWIDGET_H

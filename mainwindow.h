#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(CameraMatricesWidget)
QT_FORWARD_DECLARE_CLASS(ExtrinsicControlWidget)
QT_FORWARD_DECLARE_CLASS(IntrinsicControlWidget)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CameraMatricesWidget* _cameraMatricesWidget;

private:
    Camera* _camera;

    ExtrinsicControlWidget* _extrinsicControlWidget;
    IntrinsicControlWidget* _intrinsicControlWidget;
};

#endif // MAINWINDOW_H

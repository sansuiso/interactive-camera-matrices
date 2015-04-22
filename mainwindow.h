#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(CameraMatricesWidget)
QT_FORWARD_DECLARE_CLASS(ExtrinsicControlWidget)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CameraMatricesWidget* _cameraMatricesWidget;
    ExtrinsicControlWidget* _extrinsicControlWidget;
};

#endif // MAINWINDOW_H

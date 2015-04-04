#ifndef CAMERAMATRICESWIDGET_H
#define CAMERAMATRICESWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(Camera)

class CameraMatricesWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit CameraMatricesWidget(QWidget *parent = 0);
    ~CameraMatricesWidget();

signals:

public slots:

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram* _program;

    Camera* _camera;
};

#endif // CAMERAMATRICESWIDGET_H

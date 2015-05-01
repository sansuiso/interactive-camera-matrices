#ifndef CAMERAMATRICESWIDGET_H
#define CAMERAMATRICESWIDGET_H

#include <list>

#include <QOpenGLWidget>
#include <QMatrix4x4>

#include "modelinstance.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(Camera)

class CameraMatricesWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit CameraMatricesWidget(Camera* camera, QWidget *parent = 0);
    ~CameraMatricesWidget();

signals:

public slots:

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    Camera* _camera;

    QOpenGLShaderProgram* _program;

    QMatrix4x4 _projectionMatrix;
    QMatrix4x4 _worldMatrix;
    QMatrix4x4 _cameraMatrix;

    int _extrinsicLoc;
    int _projectionMatrixLoc;
    int _modelMatrixLoc;

    void buildProgram();

    float _near;
    float _far;

    std::list<ModelInstance> _instanceList;
    void populateScene();
};

#endif // CAMERAMATRICESWIDGET_H

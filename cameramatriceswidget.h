#ifndef CAMERAMATRICESWIDGET_H
#define CAMERAMATRICESWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QMatrix4x4>

#include "threedobject.h"

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
    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;

    QMatrix4x4 _projectionMatrix;
    QMatrix4x4 _worldMatrix;
    QMatrix4x4 _cameraMatrix;

    int _extrinsicLoc;
    int _projectionMatrixLoc;
    int _modelviewMatrixLoc;
    int _normalMatrixLoc;
    int _lightPosLoc;

    Camera* _camera;

    void buildProgram();

    ThreeDObject _scene;
    float _near;
    float _far;
};

#endif // CAMERAMATRICESWIDGET_H

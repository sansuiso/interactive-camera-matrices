#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "camera.h"
#include "cameramatriceswidget.h"

CameraMatricesWidget::CameraMatricesWidget(QWidget *parent)
    : QOpenGLWidget(parent), _program(nullptr)
{
    _camera = new Camera(1920, 1080);
}

CameraMatricesWidget::~CameraMatricesWidget()
{
    delete _camera;
}

void CameraMatricesWidget::initializeGL()
{
}

void CameraMatricesWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void CameraMatricesWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

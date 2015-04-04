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

}

void CameraMatricesWidget::resizeGL(int width, int height)
{

}

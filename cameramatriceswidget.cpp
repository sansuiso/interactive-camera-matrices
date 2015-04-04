#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "camera.h"
#include "cameramatriceswidget.h"

CameraMatricesWidget::CameraMatricesWidget(QWidget *parent)
    : QOpenGLWidget(parent), _program(nullptr)
{
    _camera = new Camera(800, 600);
}

CameraMatricesWidget::~CameraMatricesWidget()
{
    delete _camera;
}

QSize CameraMatricesWidget::sizeHint() const
{
    return QSize(_camera->pixelsWide(), _camera->pixelsHigh());
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

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "camera.h"
#include "cameramatriceswidget.h"

CameraMatricesWidget::CameraMatricesWidget(Camera *camera, QWidget *parent)
    : QOpenGLWidget(parent)
    , _camera(camera), _program(nullptr)
    , _near(1e-1f), _far(1e2f)
{
}

CameraMatricesWidget::~CameraMatricesWidget()
{
}

QSize CameraMatricesWidget::sizeHint() const
{
    if (_camera != nullptr) {
        return QSize(_camera->pixelsWide(), _camera->pixelsHigh());
    }

    return QOpenGLWidget::sizeHint();
}

void CameraMatricesWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    buildProgram();

    _cameraMatrix.setToIdentity();
    _cameraMatrix.translate(0, 0, -1);
}

void CameraMatricesWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    _worldMatrix.setToIdentity();

    QOpenGLVertexArrayObject::Binder vaoBinder(&_vao);
    _program->bind();

    if (_camera)
    {
        Eigen::Matrix4f extrinsic = _camera->extrinsic();
        Eigen::Matrix4f projection = _camera->glPerspective(_near, _far);

        for (int i = 0; i < 16; ++i) {
            _projectionMatrix.data()[i] = projection.data()[i];
            _worldMatrix.data()[i] = extrinsic.data()[i];
        }

        _program->setUniformValue(_extrinsicLoc, _worldMatrix);
        _program->setUniformValue(_projectionMatrixLoc, _projectionMatrix);

#ifdef DRAW_DEBUG
        glDrawArrays(GL_POINTS, 0, _scene.vertexCount());
#else
        glDrawArrays(GL_TRIANGLES, 0, _scene.triangleCount());
#endif
    }

    _program->release();
}

void CameraMatricesWidget::resizeGL(int width, int height)
{
    if (_camera) {
        _camera->setPixelMatrixSize(width, height);
    }
}

void CameraMatricesWidget::buildProgram()
{
    if (_program)
    {
        delete _program;
    }

    _program = new QOpenGLShaderProgram;

    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple.frag");
    _program->bindAttributeLocation("vertex", 0);
    _program->link();

    _program->bind();
    _extrinsicLoc = _program->uniformLocation("extrinsic");

    _projectionMatrixLoc = _program->uniformLocation("projection");

    _vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&_vao);

    _vbo.create();
    _vbo.bind();

    _vbo.allocate(_scene.data(), sizeof(GLfloat)*_scene.vertexCount());

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    _vbo.release();

    _program->release();
}

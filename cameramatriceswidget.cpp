#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

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

    _projectionMatrix.setToIdentity();
    _projectionMatrix.data()[0] = 2.0f/this->size().width();
    _projectionMatrix.data()[5] = 2.0f/this->size().height();

    _camera->setWorldPosition(0, 0, 0);
    Eigen::Matrix4f extrinsic = _camera->extrinsic();
    QMatrix4x4 extr(
                extrinsic(0,0), extrinsic(1,0), extrinsic(2,0), extrinsic(3,0),
                extrinsic(0,1), extrinsic(1,1), extrinsic(2,1), extrinsic(3,1),
                extrinsic(0,2), extrinsic(1,2), extrinsic(2,2), extrinsic(3,2),
                extrinsic(0,3), extrinsic(1,3), extrinsic(2,3), extrinsic(3,3)
                );

    _program->setUniformValue(_extrinsicLoc, extr);
    _program->setUniformValue(_projectionMatrixLoc, _projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, _scene.vertexCount());

    _program->release();
}

void CameraMatricesWidget::resizeGL(int width, int height)
{
    _camera->setPixelMatrixSize(width, height);
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
//    _program->bindAttributeLocation("normal", 1);
    _program->link();

    _program->bind();
    _extrinsicLoc = _program->uniformLocation("extrinsic");

    _projectionMatrixLoc = _program->uniformLocation("projection");

//    _modelviewMatrixLoc = _program->uniformLocation("mvMatrix");
//    _normalMatrixLoc = _program->uniformLocation("normalMatrix");
//    _lightPosLoc = _program->uniformLocation("lightPos");

//    _program->setUniformValue(_lightPosLoc, QVector3D(0, 0, 70));

    _vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&_vao);

    _vbo.create();
    _vbo.bind();

    _vbo.allocate(_scene.data(), sizeof(GLfloat)*_scene.vertexCount());

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
//    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    _vbo.release();

    _program->release();
}

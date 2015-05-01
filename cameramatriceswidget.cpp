#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "camera.h"
#include "cameramatriceswidget.h"
#include "modelassetsmanager.h"

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

        for (auto& instance : _instanceList)
        {
            renderInstance(instance);
        }
    }

    _program->release();
}

void CameraMatricesWidget::renderInstance(ModelInstance& instance) const
{
    _program->setUniformValue(_modelMatrixLoc, *(instance.transform()));
    glBindVertexArray(instance.asset()->vao);
    glDrawArrays(instance.asset()->drawType, instance.asset()->drawStart, instance.asset()->drawCount);
    glBindVertexArray(0);
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
    _modelMatrixLoc = _program->uniformLocation("model");

    populateScene();

    _program->release();
}

void CameraMatricesWidget::populateScene()
{
    qreal x = 0.0f;
    qreal y = 0.0f;
    qreal z = -10.0f;

    ModelInstance squareInstance(assets::squareAsset(0));
    squareInstance.moveTo(x, y, z);
    _instanceList.push_back(squareInstance);

    ModelInstance topLeftSquare(assets::squareAsset(0));
    topLeftSquare.moveTo(x-2.0, y+2.0, z);
    _instanceList.push_back(topLeftSquare);

    ModelInstance topRightSquare(assets::squareAsset(0));
    topRightSquare.moveTo(x+2.0, y+2.0, z);
    _instanceList.push_back(topRightSquare);

    ModelInstance bottomLeftSquare(assets::squareAsset(0));
    bottomLeftSquare.moveTo(x-2.0, y-2.0, z);
    _instanceList.push_back(bottomLeftSquare);

    ModelInstance bottomRightSquare(assets::squareAsset(0));
    bottomRightSquare.moveTo(x+2.0, y-2.0, z);
    _instanceList.push_back(bottomRightSquare);
}

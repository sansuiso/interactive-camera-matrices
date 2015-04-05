#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "camera.h"
#include "cameramatriceswidget.h"

static GLfloat const data3d[] = {
    0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
};

//static const char *vertexShaderSourceCore =
//    "#version 150\n"
//    "in vec4 vertex;\n"
//    "in vec3 normal;\n"
//    "out vec3 vert;\n"
//    "out vec3 vertNormal;\n"
//    "uniform mat4 projMatrix;\n"
//    "uniform mat4 mvMatrix;\n"
//    "uniform mat3 normalMatrix;\n"
//    "void main() {\n"
//    "   vert = vertex.xyz;\n"
//    "   vertNormal = normalMatrix * normal;\n"
//    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
//    "}\n";

//static const char *fragmentShaderSourceCore =
//    "#version 150\n"
//    "in highp vec3 vert;\n"
//    "in highp vec3 vertNormal;\n"
//    "out highp vec4 fragColor;\n"
//    "uniform highp vec3 lightPos;\n"
//    "void main() {\n"
//    "   highp vec3 L = normalize(lightPos - vert);\n"
//    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
//    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
//    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
//    "   fragColor = vec4(1, 1, 1, 1);\n/* vec4(col, 1.0);\n*/"
//    "}\n";

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "uniform mat4 extrinsic;\n"
    "in vec3 vertex;\n"
    "void main() {\n"
    "   gl_Position = extrinsic * vec4(vertex, 1);\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "out highp vec4 fragColor;\n"
    "void main() {\n"
    "   fragColor = vec4(1, 1, 1, 1);\n"
    "}\n";

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

    QMatrix4x4 extrinsic;
    extrinsic.setToIdentity();

    _program->setUniformValue(_extrinsicLoc, extrinsic);

//    _program->setUniformValue(_projectionMatrixLoc, _projectionMatrix);
//    _program->setUniformValue(_modelviewMatrixLoc, _cameraMatrix * _worldMatrix);
//    QMatrix3x3 normalMatrix = _worldMatrix.normalMatrix();
//    _program->setUniformValue(_normalMatrixLoc, normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    _program->release();
}

void CameraMatricesWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

void CameraMatricesWidget::buildProgram()
{
    if (_program)
    {
        delete _program;
    }

    _program = new QOpenGLShaderProgram;

    _program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    _program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    _program->bindAttributeLocation("vertex", 0);
//    _program->bindAttributeLocation("normal", 1);
    _program->link();

    _program->bind();
    _extrinsicLoc = _program->uniformLocation("extrinsic");

//    _projectionMatrixLoc = _program->uniformLocation("projMatrix");
//    _modelviewMatrixLoc = _program->uniformLocation("mvMatrix");
//    _normalMatrixLoc = _program->uniformLocation("normalMatrix");
//    _lightPosLoc = _program->uniformLocation("lightPos");

//    _program->setUniformValue(_lightPosLoc, QVector3D(0, 0, 70));

    _vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&_vao);

    _vbo.create();
    _vbo.bind();

    _vbo.allocate(data3d, sizeof(data3d));

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
//    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    _vbo.release();

    _program->release();
}

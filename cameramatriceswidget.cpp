#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "camera.h"
#include "cameramatriceswidget.h"

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
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
    buildProgram();
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
    _program->bindAttributeLocation("normal", 1);
    _program->link();

    _program->bind();
    _projectionMatrixLoc = _program->uniformLocation("projMatrix");
    _modelviewMatrixLoc = _program->uniformLocation("mvMatrix");
    _normalMatrixLoc = _program->uniformLocation("normalMatrix");
    _lightPosLoc = _program->uniformLocation("lightPos");
    _program->release();
}

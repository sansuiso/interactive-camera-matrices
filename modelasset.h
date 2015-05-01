#ifndef MODELASSET_H
#define MODELASSET_H

#include <cstdlib>
#include <gl3.h>

using std::size_t;

struct ModelAsset
{
    GLuint vbo;
    GLuint vao;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;

    ModelAsset() :
        vbo(0), vao(0), drawType(GL_TRIANGLES), drawStart(0), drawCount(0) {}

    void loadData(GLfloat const* data, size_t dataSize, GLuint vertexGeometryIndex,
                  GLenum usage = GL_STATIC_DRAW) const;
};

#endif // MODELASSET_H

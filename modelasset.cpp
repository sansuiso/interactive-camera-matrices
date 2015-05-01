#include <cassert>

#include "modelasset.h"

void ModelAsset::loadData(const GLfloat *data, size_t dataSize, GLuint vertexGeometryIndex, GLenum usage) const
{
    assert(this->vao && this->vbo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, dataSize, data, usage);

    glEnableVertexAttribArray(vertexGeometryIndex);
    glVertexAttribPointer(vertexGeometryIndex, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);

    glBindVertexArray(0);
}

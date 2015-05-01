#include <cassert>

#include "modelassetsmanager.h"

namespace assets {

static GLfloat const SQUARE_DATA[] = {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,

    -0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
};

ModelAsset* squareAsset(GLuint vertexGeometryIndex)
{
    static ModelAsset* _sharedSquareAsset = nullptr;

    if (!_sharedSquareAsset)
    {
        _sharedSquareAsset = new ModelAsset;
        assert(_sharedSquareAsset);

        glGenBuffers(1, &_sharedSquareAsset->vbo);
        glGenVertexArrays(1, &_sharedSquareAsset->vao);

        _sharedSquareAsset->drawType = GL_TRIANGLES;
        _sharedSquareAsset->drawCount = sizeof(SQUARE_DATA)/sizeof(SQUARE_DATA[0]);

        _sharedSquareAsset->loadData(SQUARE_DATA, sizeof(SQUARE_DATA), vertexGeometryIndex);
    }

    return _sharedSquareAsset;
}

} // namespace assets

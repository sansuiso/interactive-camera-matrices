#ifndef MODELASSETSMANAGER_H
#define MODELASSETSMANAGER_H

#include "modelasset.h"

class ModelAssetsManager
{
public:
    ModelAssetsManager();

    ModelAsset* squareAsset(GLuint vertexGeometryIndex);
};

#endif // MODELASSETSMANAGER_H

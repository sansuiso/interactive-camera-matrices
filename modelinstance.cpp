#include "modelasset.h"
#include "modelinstance.h"

ModelInstance::ModelInstance(ModelAsset *asset)
    : _asset(asset)
{
    _transform.setToIdentity();
}

void ModelInstance::moveTo(float x, float y, float z)
{
    _transform.translate(x, y, z);
}


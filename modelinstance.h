#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include <QMatrix4x4>

struct ModelAsset;

class ModelInstance
{
public:
    ModelInstance(ModelAsset* asset);

    void moveTo(float x, float y, float z);

    QMatrix4x4* transform() {
        return &_transform;
    }

    ModelAsset* asset() {
        return _asset;
    }

private:
    ModelAsset* _asset;

    QMatrix4x4 _transform;
};

#endif // MODELINSTANCE_H

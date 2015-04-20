#include "threedobject.h"

static float const Z = -1.0f;

ThreeDObject::ThreeDObject(QObject *parent) : QObject(parent)
{
    _data.resize(3*3);

    _data[0] =  0.0f;
    _data[1] = 1.0f;
    _data[2] = Z;

    _data[3] = -1.0f;
    _data[4] = -1.0f;
    _data[5] = Z;

    _data[6] = 1.0f;
    _data[7] = -1.0f;
    _data[8] = Z;
}

ThreeDObject::~ThreeDObject()
{

}


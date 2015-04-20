#include "threedobject.h"

ThreeDObject::ThreeDObject(QObject *parent) : QObject(parent)
{
    _data.resize(3*3);

    _data[0] =  0.0f;
    _data[1] = 300.0f;
    _data[2] = -1.0f;

    _data[3] = -400.0f;
    _data[4] = -300.0f;
    _data[5] = -1.0f;

    _data[6] = 400.0f;
    _data[7] = -300.0f;
    _data[8] = -1.0f;
}

ThreeDObject::~ThreeDObject()
{

}


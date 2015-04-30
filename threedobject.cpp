#include "threedobject.h"

static float const Z = -10.0f;

static GLfloat const SQUARE_DATA[] = {
//    -0.5f,  0.5f, 0.0f,
//    -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,

//    -0.5f,  0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.5f,  0.5f, 0.0f,

    -0.5f,  0.5f, Z,
    -0.5f, -0.5f, Z,
     0.5f, -0.5f, Z,

    -0.5f,  0.5f, Z,
     0.5f, -0.5f, Z,
     0.5f,  0.5f, Z,
};

ThreeDObject::ThreeDObject(QObject *parent) : QObject(parent)
{
    unsigned int npoints = sizeof(SQUARE_DATA)/sizeof(SQUARE_DATA[0]);
    _data.resize(npoints);

    for (unsigned i = 0; i < npoints; ++i)
    {
        _data[i] = SQUARE_DATA[i];
    }
}

ThreeDObject::~ThreeDObject()
{

}


#include "camera.h"

Camera::Camera(int pixelsWide, int pixelsHigh)
    : _pixelsWide(pixelsWide), _pixelsHigh(pixelsHigh), _micronsPerPixel(3)
    , _x(0), _y(0), _z(0)
{

}

Camera::~Camera()
{

}

int Camera::pixelsWide() const
{
    return _pixelsWide;
}

int Camera::pixelsHigh() const
{
    return _pixelsHigh;
}

void Camera::setWorldPosition(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

Eigen::Matrix4f Camera::extrinsic()
{
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0,3) = -_x;
    translation(1,3) = -_y;
    translation(2,3) = -_z;

    Eigen::Matrix4f orientation = Eigen::Matrix4f::Identity();

    return orientation * translation;
}

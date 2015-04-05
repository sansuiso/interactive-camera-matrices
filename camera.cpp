#include "camera.h"

Camera::Camera(int pixelsWide, int pixelsHigh)
    : _pixelsWide(pixelsWide), _pixelsHigh(pixelsHigh), _micronsPerPixel(3)
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

Eigen::Matrix4f Camera::extrinsic()
{
    return Eigen::Matrix4f::Identity();
}

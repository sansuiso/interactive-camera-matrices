#include <math.h>
#include "camera.h"

Camera::Camera(int pixelsWide, int pixelsHigh)
    : _pixelsWide(pixelsWide), _pixelsHigh(pixelsHigh), _micronsPerPixel(3)
    , _x(0), _y(0), _z(0), _theta_x(0), _theta_y(M_PI_4), _theta_z(0)
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

void Camera::setWorldOrientation(float theta_x, float theta_y, float theta_z)
{
    _theta_x = theta_x;
    _theta_y = theta_y;
    _theta_z = theta_z;
}

Eigen::Matrix4f Camera::extrinsic()
{
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0,3) = -_x;
    translation(1,3) = -_y;
    translation(2,3) = -_z;

    Eigen::Matrix3f Rx = Eigen::Matrix3f::Identity();
    Rx(1,1) = cosf(_theta_x);
    Rx(1,2) = -sinf(_theta_x);
    Rx(2,1) = sinf(_theta_x);
    Rx(2,2) = cosf(_theta_x);

    Eigen::Matrix3f Ry = Eigen::Matrix3f::Identity();
    Ry(0,0) = cosf(_theta_y);
    Ry(2,0) = -sinf(_theta_y);
    Ry(0,2) = sinf(_theta_y);
    Ry(2,2) = cosf(_theta_y);

    Eigen::Matrix3f Rz = Eigen::Matrix3f::Identity();
    Rz(0,0) = cosf(_theta_z);
    Rz(0,1) = -sinf(_theta_z);
    Rz(1,0) = sinf(_theta_z);
    Rz(1,1) = cosf(_theta_z);

    Eigen::Matrix3f Rc = Rx*Ry*Rz;

    Eigen::Matrix4f orientation = Eigen::Matrix4f::Identity();
    orientation.block(0, 0, 3, 3) = Rc.transpose();

    return orientation * translation;
}

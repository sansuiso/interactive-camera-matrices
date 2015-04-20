#include <math.h>
#include "camera.h"

Camera::Camera(int pixelsWide, int pixelsHigh)
    : _pixelsWide(pixelsWide), _pixelsHigh(pixelsHigh), _micronsPerPixel(3)
    , _x(0), _y(0), _z(0), _theta_x(0), _theta_y(0), _theta_z(0)
    , _focalLength(1)
{

}

Camera::~Camera()
{

}

void Camera::setPixelMatrixSize(int width, int height)
{
    _pixelsWide = width;
    _pixelsHigh = height;
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
    struct deg2rad
    {
        deg2rad(float degrees)
        {
            while(degrees > 360.0f) degrees -= 360.0f;
            while(degrees < 0.0f) degrees += 360.0f;

            value = M_PI * degrees / 180.0f;
        }

        float value;
    };

    _theta_x = deg2rad(theta_x).value;
    _theta_y = deg2rad(theta_y).value;
    _theta_z = deg2rad(theta_z).value;
}

Eigen::Matrix3f Camera::intrinsic()
{
    Eigen::Matrix3f K = Eigen::Matrix3f::Identity();

    K(0,0) = (_focalLength*1e-3f) / (_micronsPerPixel*1e-6);
    K(1,1) = (_focalLength*1e-3f) / (_micronsPerPixel*1e-6);

    K(0,2) = -_pixelsWide/2;
    K(1,2) = -_pixelsHigh/2;

    return K;
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

Eigen::Matrix4f Camera::projection()
{
    Eigen::Matrix3f K = intrinsic();

    /*
     *  - x, y are projected
     *  - z is kept as is
     *  - w <--- z
     */

    // Apply camera to x, y
    Eigen::Matrix4f extendedK = Eigen::Matrix4f::Zero();
    extendedK(0,0) = K(0,0);
    extendedK(1,1) = K(1,1);

    // Preserve z
    extendedK(2, 2) = 1;
    // w <--- z
    extendedK(3, 3) = 1;

    Eigen::Matrix4f P = extendedK /* * extrinsic()*/;

    return P;
}

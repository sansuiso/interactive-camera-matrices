#include <math.h>
#include <iostream>

#include "camera.h"

Camera::Camera(int pixelsWide, int pixelsHigh)
    : _pixelsWide(pixelsWide), _pixelsHigh(pixelsHigh), _micronsPerPixel(1)
    , _x(0), _y(0), _z(0), _theta_x(0), _theta_y(0), _theta_z(0)
    , _focalLength(1), _pixelAspectRatio(1), _skew(0), _x0(0), _y0(0)
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

Eigen::Matrix3f Camera::intrinsic() const
{
    Eigen::Matrix3f K = Eigen::Matrix3f::Identity();

    K(0,0) = _focalLength * 1e-3 / (_micronsPerPixel*1e-6);
    K(0,1) = _skew;
    K(1,1) = _pixelAspectRatio * K(0,0);

    K(0,2) = _x0 / (_micronsPerPixel*1e-6);
    K(1,2) = _y0 * _pixelAspectRatio / (_micronsPerPixel*1e-6);

    return K;
}

Eigen::Matrix4f Camera::extrinsic() const
{
    Eigen::Vector3f C;
    C << -_x, -_y, -_z;

    Eigen::Matrix3f Rx = Eigen::Matrix3f::Identity();
    Rx(1,1) = cosf(-_theta_x);
    Rx(1,2) = -sinf(-_theta_x);
    Rx(2,1) = sinf(-_theta_x);
    Rx(2,2) = cosf(-_theta_x);

    Eigen::Matrix3f Ry = Eigen::Matrix3f::Identity();
    Ry(0,0) = cosf(-_theta_y);
    Ry(2,0) = -sinf(-_theta_y);
    Ry(0,2) = sinf(-_theta_y);
    Ry(2,2) = cosf(-_theta_y);

    Eigen::Matrix3f Rz = Eigen::Matrix3f::Identity();
    Rz(0,0) = cosf(-_theta_z);
    Rz(0,1) = -sinf(-_theta_z);
    Rz(1,0) = sinf(-_theta_z);
    Rz(1,1) = cosf(-_theta_z);

    Eigen::Matrix3f Rc = Rx*Ry*Rz;

    Eigen::Matrix4f extr = Eigen::Matrix4f::Identity();
    extr.block(0, 0, 3, 3) = Rc;
    extr.block(0, 3, 3, 1) = C;

    return extr;
}

Eigen::Matrix4f Camera::glPerspective(float near, float far)
{
    Eigen::Matrix4f perspective = Eigen::Matrix4f::Zero();

    Eigen::Matrix3f K = intrinsic();

    perspective(0,0) = K(0,0);
    perspective(1,1) = K(1,1);

    perspective(0,1) = K(0,1);

    perspective(0,2) = -K(0,2);
    perspective(1,2) = -K(1,2);
    perspective(3,2) = -1;

    perspective(2,2) = near + far;
    perspective(2,3) = near*far;

    Eigen::Matrix4f NDC = Eigen::Matrix4f::Identity();

    float right = _pixelsWide/2;
    float left = -right;
    float top = _pixelsHigh/2;
    float bottom = -top;

    NDC(0,0) = 2.0f / (right - left);
    NDC(1,1) = 2.0f / (top - bottom);
    NDC(2,2) = -2.0f / (far - near);
    NDC(0,3) = -(right + left)/(right - left);
    NDC(1,3) = -(top + bottom)/(top - bottom);
    NDC(2,3) = -(far + near)/(far - near);

    Eigen::Matrix4f P = NDC * perspective;

    return P;
}

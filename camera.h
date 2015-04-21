#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

class Camera
{
public:
    Camera(int pixelsWide, int pixelsHigh);
    ~Camera();

    void setWorldPosition(float x, float y, float z);
    void setWorldOrientation(float theta_x, float theta_y, float theta_z);

    void setPixelSize(float microns);
    void setPixelMatrixSize(int width, int height);

    int pixelsWide() const;
    int pixelsHigh() const;

    void setFocalLength(float f_mm) {
        _focalLength = f_mm;
    }

    float focalLength() const {
        return _focalLength * 1e-3;
    }

    float cameraPlaneOriginX() const {
        return _x0;
    }

    void setCameraPlaneOriginX(float x) {
        _x0 = x;
    }

    float cameraPlaneOriginY() const {
        return _y0;
    }

    void setCameraPlaneOriginY(float y) {
        _y0 = y;
    }

    float sensorWidth() const {
        return _micronsPerPixel*pixelsWide()*1e-6;
    }

    float sensorHeight() const {
        return _micronsPerPixel*pixelsHigh()*1e-6;
    }

    Eigen::Matrix3f intrinsic();
    Eigen::Matrix4f extrinsic();
    Eigen::Matrix4f glPerspective(float left, float right, float bottom, float top, float near, float far);

private:
    int _pixelsWide;
    int _pixelsHigh;
    float _micronsPerPixel;

    float _x, _y, _z;
    float _theta_x, _theta_y, _theta_z;
    float _focalLength;
    float _pixelAspectRatio;
    float _skew;

    float _x0;
    float _y0;
};

#endif // CAMERA_H

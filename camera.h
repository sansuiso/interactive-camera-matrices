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

    Eigen::Matrix3f intrinsic();
    Eigen::Matrix4f extrinsic();
    Eigen::Matrix4f projection();

private:
    int _pixelsWide;
    int _pixelsHigh;
    float _micronsPerPixel;

    float _x, _y, _z;
    float _theta_x, _theta_y, _theta_z;
    float _focalLength;
};

#endif // CAMERA_H

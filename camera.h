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

    Eigen::Matrix4f extrinsic();

private:
    int _pixelsWide;
    int _pixelsHigh;
    float _micronsPerPixel;
};

#endif // CAMERA_H

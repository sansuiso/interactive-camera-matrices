#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

class Camera
{
public:
    Camera(int pixelsWide=800, int pixelsHigh=600);
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

    float FNumber() const {
        return _focalLength;
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
    Eigen::Matrix4f extrinsic() const;
    Eigen::Matrix4f glPerspective(float near, float far);

    float micronsPerPixel() const {
        return _micronsPerPixel;
    }

    void setMicronsPerPixel(float value) {
        _micronsPerPixel = value > 1.0f ? value : 1.0f;
    }

    float skew() const {
        return _skew;
    }

    void setSkew(float skew) {
        _skew = skew;
    }

    void setAspectRatio(float ratio) {
        _pixelAspectRatio = ratio;
    }

    float aspectRatio() const {
        return _pixelAspectRatio;
    }

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

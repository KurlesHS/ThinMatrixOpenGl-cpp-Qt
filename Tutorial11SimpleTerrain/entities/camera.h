#ifndef CAMERA_H
#define CAMERA_H

#include <QSharedPointer>
#include <QVector3D>

class Camera;

using CameraSharedPtr = QSharedPointer<Camera>;

class Camera
{
public:

    Camera();
    Camera(const QVector3D &position,
           const float &pitch,
           const float &yaw,
           const float &roll);

    void move();

    QVector3D position() const;
    float pitch() const;
    float yaw() const;
    float roll() const;



private:
    QVector3D mPosition;
    float mPitch;
    float mYaw;
    float mRoll;
};

#endif // CAMERA_H

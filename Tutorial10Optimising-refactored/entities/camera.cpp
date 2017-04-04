#include "camera.h"

#include <toolbox/keyboard.h>

#include <QDebug>

Camera::Camera() :
    Camera(QVector3D(0, 0, 0), 0, 0, 0)
{

}

Camera::Camera(const QVector3D &position, const float &pitch, const float &yaw, const float &roll) :
    mPosition(position),
    mPitch(pitch),
    mYaw(yaw),
    mRoll(roll)
{

}

void Camera::move()
{
    Keyboard *keyManager = Keyboard::instance();
    if (keyManager->isKeyPressed(Qt::Key_W)) {        
        mPosition += QVector3D(0, 0, -2);
    }

    if (keyManager->isKeyPressed(Qt::Key_S)) {
        mPosition += QVector3D(0, 0, 2);
    }

    if (keyManager->isKeyPressed(Qt::Key_D)) {
        mPosition += QVector3D(2, 0, 0);
    }
    if (keyManager->isKeyPressed(Qt::Key_A)) {
        mPosition += QVector3D(-2, 0, 0);
    }
}

float Camera::pitch() const
{
    return mPitch;
}

float Camera::yaw() const
{
    return mYaw;
}

float Camera::roll() const
{
    return mRoll;
}

QVector3D Camera::position() const
{
    return mPosition;
}


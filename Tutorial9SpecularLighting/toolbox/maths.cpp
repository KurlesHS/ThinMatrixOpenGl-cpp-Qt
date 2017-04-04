#include "maths.h"

Maths::Maths()
{

}

QMatrix4x4 Maths::createTransformationMatrix(const QVector3D translation, const float &rx, const float &ry, const float &rz, const float scale)
{
    QMatrix4x4 result;
    result.setToIdentity();
    result.translate(translation);
    result.rotate(rx, QVector3D(1, 0, 0));
    result.rotate(ry, QVector3D(0, 1, 0));
    result.rotate(rz, QVector3D(0, 0, 1));
    result.scale(scale);
    return result;
}

QMatrix4x4 Maths::createViewMatrix(CameraSharedPtr camera)
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.rotate(camera->pitch(), 1, 0, 0);
    viewMatrix.rotate(camera->yaw(), 0, 1, 0);
    auto cameraPos = camera->position();
    auto negativeCameraPos = QVector3D(0, 0, 0) - cameraPos;
    viewMatrix.translate(negativeCameraPos);
    return viewMatrix;

}

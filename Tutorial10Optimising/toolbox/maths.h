#ifndef MATHS_H
#define MATHS_H

#include <QMatrix4x4>
#include <entities/camera.h>

class Maths
{
public:
    Maths();

    static QMatrix4x4 createTransformationMatrix(const QVector3D translation, const float &rx, const float &ry, const float &rz, const float scale);
    static QMatrix4x4 createViewMatrix(CameraSharedPtr camera);
};

#endif // MATHS_H

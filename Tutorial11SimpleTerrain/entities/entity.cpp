#include "entity.h"

Entity::Entity(const TexturedModelSharedPtr &model, const QVector3D &position, const float &rotX, const float &rotY, const float &rotZ, const float &scale) :
    mModel(model),
    mPosition(position),
    mRotX(rotX),
    mRotY(rotY),
    mRotZ(rotZ),
    mScale(scale)
{

}

void Entity::increasePosition(const float &dx, const float &dy, const float &dz)
{
    mPosition += QVector3D(dx, dy, dz);
}

void Entity::increaseRotation(const float &dx, const float &dy, const float &dz)
{
    mRotX += dx;
    mRotY += dy;
    mRotZ += dz;
}

TexturedModelSharedPtr Entity::model() const
{
    return mModel;
}

QVector3D Entity::position() const
{
    return mPosition;
}

float Entity::rotX() const
{
    return mRotX;
}

float Entity::rotY() const
{
    return mRotY;
}

float Entity::rotZ() const
{
    return mRotZ;
}

float Entity::scale() const
{
    return mScale;
}

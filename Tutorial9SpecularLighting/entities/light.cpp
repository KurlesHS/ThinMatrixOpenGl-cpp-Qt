#include "light.h"

Light::Light(const QVector3D &position, const QVector3D &color) :
    mPosition(position),
    mColor(color)
{

}

QVector3D Light::position() const
{
    return mPosition;
}

void Light::setPosition(const QVector3D &position)
{
    mPosition = position;
}

QVector3D Light::color() const
{
    return mColor;
}

void Light::setColor(const QVector3D &color)
{
    mColor = color;
}

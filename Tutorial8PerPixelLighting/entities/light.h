#ifndef LIGHT_H
#define LIGHT_H

#include <QSharedPointer>
#include <QVector3D>

class Light;

using LightSharedPtr = QSharedPointer<Light>;

class Light
{
public:
    Light(const QVector3D &position, const QVector3D &color);

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QVector3D color() const;
    void setColor(const QVector3D &color);

private:
    QVector3D mPosition;
    QVector3D mColor;


};

#endif // LIGHT_H

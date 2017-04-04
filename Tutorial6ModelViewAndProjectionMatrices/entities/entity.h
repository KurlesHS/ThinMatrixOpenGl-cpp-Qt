#ifndef ENTITY_H
#define ENTITY_H

#include <models/texturedmodel.h>

#include <QSharedPointer>

class Entity;

using EntitySharedPtr = QSharedPointer<Entity>;

class Entity
{
public:
    Entity(const TexturedModelSharedPtr &model,
           const QVector3D &position,
           const float &rotX,
           const float &rotY,
           const float &rotZ,
           const float &scale);

    void increasePosition(const float &dx,
                          const float &dy,
                          const float &dz);

    void increaseRotation(const float &dx,
                          const float &dy,
                          const float &dz);

    TexturedModelSharedPtr model() const;
    QVector3D position() const;
    float rotX() const;
    float rotY() const;
    float rotZ() const;
    float scale() const;

private:
    const TexturedModelSharedPtr mModel;
    QVector3D mPosition;
    float mRotX;
    float mRotY;
    float mRotZ;
    const float mScale;
};

#endif // ENTITY_H

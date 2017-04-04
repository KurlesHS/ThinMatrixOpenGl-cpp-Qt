#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "staticshader.h"
#include <entities/entity.h>
#include <models/texturedmodel.h>

#include <QHash>

class Renderer;

class MasterRenderer
{
public:
    MasterRenderer();
    ~MasterRenderer();

public:
    void cleanUp();

    void render(LightSharedPtr sun, CameraSharedPtr camera);

    void processEntity(EntitySharedPtr entity);

    StaticShader *shader() const;
    void setShader(StaticShader *shader);

    Renderer *renderer() const;
    void setRenderer(Renderer *renderer);

private:
    StaticShader *mShader;
    Renderer *mRenderer;

    QHash<TexturedModelSharedPtr, QList<EntitySharedPtr>> mEntities;
};

#endif // MASTERRENDERER_H

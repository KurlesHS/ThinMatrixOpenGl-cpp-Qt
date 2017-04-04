#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "staticshader.h"
#include <entities/entity.h>
#include <models/texturedmodel.h>
#include "irenderer.h"

#include <QHash>

class DisplayManager;
class EntityRenderer;
class Loader;

class MasterRenderer : public IRenderer
{
public:
    static constexpr float FOV = 70;
    static constexpr float NearPlane = 0.1;
    static constexpr float FarPlane = 1000.;

    MasterRenderer(DisplayManager *displayManager);
    ~MasterRenderer();



    // IRenderer interface
public:
    virtual void render() override;
    void prepare();

public:
    void cleanUp();
    void render(LightSharedPtr sun, CameraSharedPtr camera);
    void processEntity(EntitySharedPtr entity);

private:
    void createProjectionMatrix();

private:
    Loader *mLoader;
    StaticShader *mShader;
    EntityRenderer *mEntityRenderer;
    DisplayManager *mDisplayManager;
    QMatrix4x4 mProjectionMatrix;
    CameraSharedPtr mCamera;
    LightSharedPtr mLight;
    TexturedModelSharedPtr mTexturedCubeModel;


    QHash<TexturedModelSharedPtr, QList<EntitySharedPtr>> mEntities;
    QList<EntitySharedPtr> mCubes;


};

#endif // MASTERRENDERER_H

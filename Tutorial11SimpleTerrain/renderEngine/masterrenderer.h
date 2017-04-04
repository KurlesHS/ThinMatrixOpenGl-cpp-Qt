#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "staticshader.h"
#include <entities/entity.h>
#include <models/texturedmodel.h>
#include <terrains/terrain.h>

#include "irenderer.h"

#include <QHash>

class Loader;
class TerrainShader;
class DisplayManager;
class EntityRenderer;
class TerrainRenderer;

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
    void processTerrain(TerrainSharedPtr terrain);


private:
    void createProjectionMatrix();

private:
    Loader *mLoader;
    StaticShader *mStaticShader;
    TerrainShader *mTerrainShader;
    EntityRenderer *mEntityRenderer;
    TerrainRenderer *mTerrainRenderer;
    DisplayManager *mDisplayManager;
    QMatrix4x4 mProjectionMatrix;
    CameraSharedPtr mCamera;
    LightSharedPtr mLight;
    TexturedModelSharedPtr mTexturedCubeModel;


    QHash<TexturedModelSharedPtr, QList<EntitySharedPtr>> mEntities;
    QList<EntitySharedPtr> mCubes;
    QList<TerrainSharedPtr> mTerrains;

    QList<TerrainSharedPtr> mSourceTerrains;


};

#endif // MASTERRENDERER_H

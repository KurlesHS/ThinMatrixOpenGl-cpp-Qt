#include "masterrenderer.h"

#include "entityrenderer.h"
#include "displaymanager.h"
#include "terrainrenderer.h"

#include "terrainshader.h"

#include <renderEngine/loader.h>
#include <renderEngine/objloader.h>

#include <toolbox/misc.h>

MasterRenderer::MasterRenderer(DisplayManager *displayManager) :
    mLoader(new Loader()),
    mStaticShader(new StaticShader()),
    mTerrainShader(new TerrainShader()),
    mDisplayManager(displayManager)

{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    createProjectionMatrix();
    mStaticShader->init();
    if (!mStaticShader->isValid()) {
        qDebug() << mStaticShader->lastError();
        return;
    }

    mTerrainShader->init();
    if (!mTerrainShader->isValid()) {
        qDebug() << "terrain shader error: " << mTerrainShader->lastError();
        return;
    }

    mEntityRenderer = new EntityRenderer(mStaticShader, mProjectionMatrix);
    mTerrainRenderer = new TerrainRenderer(mTerrainShader, mProjectionMatrix);
    mLight = LightSharedPtr::create(QVector3D(20000,20000,2000), QVector3D(1, 1, 1));
    mCamera = CameraSharedPtr::create();


    auto model = ObjLoader::loadObjModel(Misc::resourceFilePath("resources/models/ColoredCube.obj"), mLoader);
    auto texture = ModelTexture(mLoader->loadTexture(Misc::resourceFilePath("resources/textures/gradient.png")));

    mTexturedCubeModel = TexturedModelSharedPtr::create(model, texture);


    auto random = []() {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return r;
    };

    for (int i = 0; i < 200; i++) {
        float x = random() * 100 - 50;
        float y = random() * 100 - 50;
        float z = random() * - 300;
        mCubes.append(EntitySharedPtr::create(mTexturedCubeModel, QVector3D(x, y, z), random() * 180.,
                                                random() * 180., 0, 1));
    }

    // Terrain(0, 0, mLoader, mLoader->loadTexture(Misc::resourceFilePath("resources/textures/grass.png")));
    // Terrain(1, 0, mLoader, mLoader->loadTexture(Misc::resourceFilePath("resources/textures/grass.png")));
    mSourceTerrains.append(TerrainSharedPtr::create(-0.5, -0.5, mLoader, mLoader->loadTexture(Misc::resourceFilePath("resources/textures/grass.png"))));
    // mSourceTerrains.append(TerrainSharedPtr::create(2, 0.5, mLoader, mLoader->loadTexture(Misc::resourceFilePath("resources/textures/grass.png"))));

}

MasterRenderer::~MasterRenderer()
{
    cleanUp();
}

void MasterRenderer::cleanUp()
{
    mStaticShader->cleanUp();
    mTerrainShader->cleanUp();
}

void MasterRenderer::render(LightSharedPtr sun, CameraSharedPtr camera)
{
    mCamera->move();
    prepare();


    if (mTerrainRenderer) {
        bool isValid = mTerrainShader->isValid();
        mTerrainShader->start();
        mTerrainShader->loadLight(sun);
        mTerrainShader->loadViewMatrix(camera);
        mTerrainRenderer->render(mTerrains);
        mTerrainShader->stop();
    }

    if (mEntityRenderer) {
        mStaticShader->start();
        mStaticShader->loadLight(sun);
        mStaticShader->loadViewMatrix(camera);
        mEntityRenderer->render(mEntities);
        mStaticShader->stop();
    }

    mTerrains.clear();
    mEntities.clear();
}

void MasterRenderer::processEntity(EntitySharedPtr entity)
{
    if (mEntityRenderer) {
        TexturedModelSharedPtr entityModel = entity->model();
        mEntities[entityModel].append(entity);
    }
}

void MasterRenderer::processTerrain(TerrainSharedPtr terrain)
{
    if (mTerrainRenderer) {
        mTerrains.append(terrain);
    }
}

void MasterRenderer::createProjectionMatrix()
{
    auto size = mDisplayManager->size();
    float aspectRatio = (float)size.width() / size.height();
    mProjectionMatrix.perspective(FOV, aspectRatio, NearPlane, FarPlane);
}

void MasterRenderer::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
}


void MasterRenderer::render()
{
    if (mEntityRenderer) {
        for (EntitySharedPtr cube : mCubes) {
            processEntity(cube);
        }
    }

    if (mTerrainRenderer) {
        for (auto terrain : mSourceTerrains) {
            processTerrain(terrain);
        }
    }
    render(mLight, mCamera);

}

#include "masterrenderer.h"
#include "entityrenderer.h"
#include "displaymanager.h"

#include <renderEngine/objloader.h>
#include <renderEngine/loader.h>

#include <toolbox/misc.h>

MasterRenderer::MasterRenderer(DisplayManager *displayManager) :
    mLoader(new Loader()),
    mShader(new StaticShader(":/shaders/shaders/shader.vert",
                             ":/shaders/shaders/shader.frag")),
    mDisplayManager(displayManager)

{

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    createProjectionMatrix();
    mShader->init();
    if (!mShader->isValid()) {
        qDebug() << mShader->lastError();
        return;
    }

    mEntityRenderer = new EntityRenderer(mShader, mProjectionMatrix);
    mLight = LightSharedPtr::create(QVector3D(3000, 2000, 2000), QVector3D(1, 1, 1));
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

}

MasterRenderer::~MasterRenderer()
{
    cleanUp();
}

void MasterRenderer::cleanUp()
{
    mShader->cleanUp();
}

void MasterRenderer::render(LightSharedPtr sun, CameraSharedPtr camera)
{
    prepare();
    mCamera->move();
    mShader->start();
    mShader->loadLight(sun);
    mShader->loadViewMatrix(camera);
    mEntityRenderer->render(mEntities);
    mShader->stop();
    mEntities.clear();
}

void MasterRenderer::processEntity(EntitySharedPtr entity)
{
    if (mEntityRenderer) {
        TexturedModelSharedPtr entityModel = entity->model();
        mEntities[entityModel].append(entity);
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

        render(mLight, mCamera);
    }
}

#include "masterrenderer.h"
#include "renderer.h"

MasterRenderer::MasterRenderer()
{

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
    mRenderer->prepare();
    mShader->start();
    mShader->loadLight(sun);
    mShader->loadViewMatrix(camera);
    mRenderer->render(mEntities);
    mShader->stop();
    mEntities.clear();
}

void MasterRenderer::processEntity(EntitySharedPtr entity)
{
    TexturedModelSharedPtr entityModel = entity->model();
    mEntities[entityModel].append(entity);
}

StaticShader *MasterRenderer::shader() const
{
    return mShader;
}

void MasterRenderer::setShader(StaticShader *shader)
{
    mShader = shader;
}

Renderer *MasterRenderer::renderer() const
{
    return mRenderer;
}

void MasterRenderer::setRenderer(Renderer *renderer)
{
    mRenderer = renderer;
}

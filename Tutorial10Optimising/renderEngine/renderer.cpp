#include "loader.h"
#include "renderer.h"

#include <textures/modeltexture.h>

#include <models/texturedmodel.h>

#include <toolbox/maths.h>
#include <toolbox/misc.h>

#include "objloader.h"

#include <QDebug>

Renderer::Renderer(DisplayManager *displayManager) :
    mDisplayManager(displayManager),
    mLoader(new Loader())
{    
    mModel = ObjLoader::loadObjModel(Misc::resourceFilePath("resources/models/ColoredCube.obj"), mLoader);
    // mModel = ObjLoader::loadObjModel(":/models/resources/models/stall.obj", mLoader);

    // auto texture = ModelTexture(mLoader->loadTexture(":/textures/resources/textures/t256_256.png"));
    // auto texture = ModelTexture(mLoader->loadTexture(":/textures/resources/textures/stallTexture.png"));
    // auto texture = ModelTexture(mLoader->loadTexture(":/textures/resources/textures/white.png"));
    auto texture = ModelTexture(mLoader->loadTexture(Misc::resourceFilePath("resources/textures/gradient.png")));
    //texture.setReflectivity(1);
    //texture.setShineDamper(10);

    mTexturedModel = TexturedModelSharedPtr::create(mModel, texture);
    mLight = LightSharedPtr::create(QVector3D(3000, 2000, 2000), QVector3D(1, 1, 1));
    mCamera = CameraSharedPtr::create();

    auto random = []() {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return r;
    };

    for (int i = 0; i < 200; i++) {
        float x = random() * 100 - 50;
        float y = random() * 100 - 50;
        float z = random() * - 300;

        Entity e(mTexturedModel, QVector3D(x, y, z), random() * 180.,
                 random() * 180., 0, 1);
        mCubes.append(EntitySharedPtr::create(mTexturedModel, QVector3D(x, y, z), random() * 180.,
                                                random() * 180., 0, 1));
    }





    mShader = new StaticShader(":/shaders/shaders/shader.vert",
                               ":/shaders/shaders/shader.frag");

    mShader->init();
    if (!mShader->isValid()) {
        qDebug() << mShader->lastError();
        return;
    }

    mEntity = EntitySharedPtr::create(mTexturedModel, QVector3D(0, 0, -25), 0, 0, 0, 1);
    // Light l(QVector3D(0, 0, -20), QVector3D(1, 1, 1));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    createProjectionMatrix();
    mShader->start();
    mShader->loadProjectionMatrix(mProjectionMatrix);
    mShader->stop();
    mMasterRenderer.setRenderer(this);
    mMasterRenderer.setShader(mShader);

}

Renderer::~Renderer()
{
    delete mLoader;
    delete mShader;
}

void Renderer::render()
{    
    mCamera->move();
    prepare();

    for (EntitySharedPtr cube : mCubes) {
        mMasterRenderer.processEntity(cube);
    }

    mMasterRenderer.render(mLight, mCamera);
    render(mEntity, mShader);

}

void Renderer::render(RawModelSharedPtr model)
{
    glBindVertexArray(model->vaoId());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model->vertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::render(TexturedModelSharedPtr model)
{
    auto rawModel = model->rawModel();
    glBindVertexArray(rawModel->vaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);    
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexturedModel->texture().textureId());
    glDrawElements(GL_TRIANGLES, rawModel->vertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::render(EntitySharedPtr entity, StaticShader *shader)
{
    TexturedModelSharedPtr model = entity->model();
    auto rawModel = model->rawModel();
    glBindVertexArray(rawModel->vaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    QMatrix4x4 transformationMatrix = Maths::createTransformationMatrix(
                entity->position(),
                entity->rotX(), entity->rotY(), entity->rotZ(),
                entity->scale());
    shader->loadTransformationMatrix(transformationMatrix);
    auto texutre = model->texture();
    shader->loadShineVariables(texutre.shineDamper(), texutre.reflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexturedModel->texture().textureId());
    glDrawElements(GL_TRIANGLES, rawModel->vertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::createProjectionMatrix()
{
    auto size = mDisplayManager->size();
    float aspectRatio = (float)size.width() / size.height();
    mProjectionMatrix.perspective(FOV, aspectRatio, NearPlane, FarPlane);
}

void Renderer::prepareTexturedModel(TexturedModelSharedPtr model)
{
    auto rawModel = model->rawModel();
    glBindVertexArray(rawModel->vaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    /* привязка текстуры */
    auto texutre = model->texture();
    mShader->loadShineVariables(texutre.shineDamper(), texutre.reflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexturedModel->texture().textureId());
}

void Renderer::unbindTexturedModel()
{
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::prepareInstance(EntitySharedPtr entity)
{
    QMatrix4x4 transformationMatrix = Maths::createTransformationMatrix(
                entity->position(),
                entity->rotX(), entity->rotY(), entity->rotZ(),
                entity->scale());
    mShader->loadTransformationMatrix(transformationMatrix);
}

StaticShader *Renderer::shader() const
{
    return mShader;
}

void Renderer::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
}

void Renderer::render(QHash<TexturedModelSharedPtr, QList<EntitySharedPtr> > entities)
{
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        TexturedModelSharedPtr model = it.key();
        QList<EntitySharedPtr> &e = it.value();
        prepareTexturedModel(model);
        for (const auto &entity : e) {
            prepareInstance(entity);
            glDrawElements(GL_TRIANGLES, model->rawModel()->vertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }
}

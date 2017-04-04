#include "loader.h"
#include "renderer.h"

#include <textures/modeltexture.h>

#include <models/texturedmodel.h>

#include <toolbox/maths.h>

#include <QDebug>

Renderer::Renderer(DisplayManager *displayManager) :
    mDisplayManager(displayManager),
    mLoader(new Loader())
{    

    QVector<GLfloat> verticles = {
        -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,0.5f,-0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,-0.5f,0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            0.5f,0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f,0.5f,
            -0.5f,0.5f,0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,0.5f,-0.5f,
            0.5f,0.5f,-0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,-0.5f,0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f
    };

    QVector<GLint> indices = {
        0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22
    };

    QVector<GLfloat> textureCoords = {
        0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0
    };

    mModel = mLoader->loadDataToVao(
                verticles,
                textureCoords,
                indices);

    auto texture = ModelTexture(mLoader->loadTexture(":/textures/resources/textures/t256_256.png"));
    mTexturedModel = TexturedModelSharedPtr::create(mModel, texture);

    mShader = new StaticShader(":/shaders/shaders/shader.vert",
                               ":/shaders/shaders/shader.frag");

    mShader->init();
    if (!mShader->isValid()) {
        qDebug() << mShader->lastError();
        return;
    }

    mCamera = CameraSharedPtr::create();
    mEntity = EntitySharedPtr::create(mTexturedModel, QVector3D(0, 0, -5), 0, 0, 0, 1);
    createProjectionMatrix();
    mShader->start();
    mShader->loadProjectionMatrix(mProjectionMatrix);
    mShader->stop();

}

Renderer::~Renderer()
{
    delete mLoader;
    delete mShader;
}

void Renderer::render()
{
    mEntity->increaseRotation(1, 1, 0);
    // mEntity->increaseRotation(0, 1, 0);
    mCamera->move();
    prepare();
    mShader->start();
    mShader->loadViewMatrix(mCamera);
    render(mEntity, mShader);
    mShader->stop();
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexturedModel->texture().textureId());
    glDrawElements(GL_TRIANGLES, rawModel->vertexCount(), GL_UNSIGNED_INT, 0);
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
    QMatrix4x4 transformationMatrix = Maths::createTransformationMatrix(
                entity->position(),
                entity->rotX(), entity->rotY(), entity->rotZ(),
                entity->scale());
    shader->loadTransformationMatrix(transformationMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexturedModel->texture().textureId());
    glDrawElements(GL_TRIANGLES, rawModel->vertexCount(), GL_UNSIGNED_INT, 0);
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

void Renderer::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
}

#include "loader.h"
#include "renderer.h"

#include <textures/modeltexture.h>

#include <QDebug>

#include <models/texturedmodel.h>

Renderer::Renderer() :
    mLoader(new Loader())
{    
    QVector<GLfloat> verticles = {
        -0.5, 0.5, 0.,
        -0.5, -0.5, 0.,
        0.5, -0.5f, 0.,
        0.5, 0.5, 0.
    };

    QVector<GLint> indices = {
        0, 1, 3,
        3, 1, 2
    };

    QVector<GLfloat> textureCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
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
    }


}

Renderer::~Renderer()
{
    delete mLoader;
    delete mShader;
}

void Renderer::render()
{
    prepare();
    mShader->start();
    render(mTexturedModel);
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


void Renderer::prepare()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

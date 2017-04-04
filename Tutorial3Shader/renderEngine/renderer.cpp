#include "loader.h"
#include "renderer.h"

#include <QDebug>

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

    mModel = mLoader->loadDataToVao(
                verticles,
                indices);


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
    render(mModel);
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


void Renderer::prepare()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

#include "loader.h"
#include "entityrenderer.h"

#include <textures/modeltexture.h>

#include <models/texturedmodel.h>

#include <toolbox/maths.h>
#include <toolbox/misc.h>

#include "objloader.h"

#include <QDebug>

EntityRenderer::EntityRenderer(StaticShader *shader, QMatrix4x4 projectionMatrix) :
    mShader(shader),
    mProjectionMatrix(projectionMatrix)
{
    initializeOpenGLFunctions();
    mShader->start();
    mShader->loadProjectionMatrix(mProjectionMatrix);
    mShader->stop();    

}

EntityRenderer::~EntityRenderer()
{

}

void EntityRenderer::prepareTexturedModel(TexturedModelSharedPtr model)
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
    glBindTexture(GL_TEXTURE_2D, model->texture().textureId());
}

void EntityRenderer::unbindTexturedModel()
{
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(EntitySharedPtr entity)
{
    QMatrix4x4 transformationMatrix = Maths::createTransformationMatrix(
                entity->position(),
                entity->rotX(), entity->rotY(), entity->rotZ(),
                entity->scale());
    mShader->loadTransformationMatrix(transformationMatrix);
}

void EntityRenderer::render(QHash<TexturedModelSharedPtr, QList<EntitySharedPtr> > entities)
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

#include "terrainrenderer.h"

#include <toolbox/maths.h>

#include <QList>

TerrainRenderer::TerrainRenderer(TerrainShader *shader, QMatrix4x4 projectionMatrix) :
    mShader(shader),
    mProjectionMatrix(projectionMatrix)
{
    initializeOpenGLFunctions();
    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->stop();
}

void TerrainRenderer::render(const QList<TerrainSharedPtr> &terrains)
{
    for (const TerrainSharedPtr &terrain : terrains) {
        prepareTerrain(terrain);
        LoadModelMatrix(terrain);
        glDrawElements(GL_TRIANGLES, terrain->model()->vertexCount(), GL_UNSIGNED_INT, 0);
        unbindTexturedModel();
    }
}


void TerrainRenderer::prepareTerrain(TerrainSharedPtr terrain)
{
    auto rawModel = terrain->model();
    glBindVertexArray(rawModel->vaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    /* привязка текстуры */
    auto texutre = terrain->texture();

    mShader->loadShineVariables(texutre.shineDamper(), texutre.reflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texutre.textureId());
}

void TerrainRenderer::unbindTexturedModel()
{
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void TerrainRenderer::LoadModelMatrix(TerrainSharedPtr terrain)
{
    QMatrix4x4 transformationMatrix = Maths::createTransformationMatrix(
                QVector3D(terrain->x(), 0, terrain->z()),
                0, 0, 0,
                1);
    mShader->loadTransformationMatrix(transformationMatrix);
}

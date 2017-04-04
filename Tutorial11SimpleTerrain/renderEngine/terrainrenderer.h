#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "terrainshader.h"

#include <models/texturedmodel.h>

#include <terrains/terrain.h>

#include <entities/entity.h>

#include <QMatrix4x4>
#include <QOpenGLFunctions_3_2_Core>

class TerrainRenderer : protected QOpenGLFunctions_3_2_Core
{
public:
    TerrainRenderer(TerrainShader *shader, QMatrix4x4 projectionMatrix);

    void render(const QList<TerrainSharedPtr> &terrains);

private:
    void prepareTerrain(TerrainSharedPtr terrain);
    void unbindTexturedModel();
    void LoadModelMatrix(TerrainSharedPtr terrain);

private:
    TerrainShader *mShader;
    QMatrix4x4 mProjectionMatrix;
};

#endif // TERRAINRENDERER_H

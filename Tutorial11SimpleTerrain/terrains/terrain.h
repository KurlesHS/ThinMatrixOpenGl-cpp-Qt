#ifndef TERRAIN_H
#define TERRAIN_H

#include <models/rawmodel.h>
#include <textures/modeltexture.h>

#include <QSharedPointer>

class Loader;
class Terrain;

using TerrainSharedPtr = QSharedPointer<Terrain>;


class Terrain
{
    static constexpr float SIZE = 800;
    static constexpr float VERTEX_COUNT = 128;
public:
    Terrain(float gridX, float gridZ, Loader *loader, ModelTexture texture);

    float x() const;
    float z() const;

    RawModelSharedPtr model() const;
    ModelTexture texture() const;


private:
    RawModelSharedPtr generateTerrain(Loader *loader);

private:
    float mX;
    float mZ;
    ModelTexture mTexture;
    RawModelSharedPtr mModel;




};

#endif // TERRAIN_H

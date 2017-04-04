#include "terrain.h"

#include <renderEngine/loader.h>

Terrain::Terrain(float gridX, float gridZ, Loader *loader, ModelTexture texture) :
    mX(gridX * SIZE),
    mZ(gridZ * SIZE),
    mTexture(texture),
    mModel(generateTerrain(loader))
{

}

RawModelSharedPtr Terrain::generateTerrain(Loader *loader)
{
    int count = VERTEX_COUNT * VERTEX_COUNT;
    QVector<float> vertices;
    vertices.resize(count * 3);

    QVector<float> normals;
    normals.resize(count * 3);

    QVector<float> textureCoords;
    textureCoords.resize(count * 2);

    QVector<int> indices;
    indices.resize(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));

    int pointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[pointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[pointer*3+1] = 0;
            vertices[pointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            normals[pointer*3] = 0;
            normals[pointer*3+1] = 1;
            normals[pointer*3+2] = 0;
            textureCoords[pointer*2] = (float)j/((float)VERTEX_COUNT - 1);
            textureCoords[pointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
            pointer++;
        }
    }
    pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader->loadDataToVao(vertices, textureCoords, normals, indices);
}

ModelTexture Terrain::texture() const
{
    return mTexture;
}

RawModelSharedPtr Terrain::model() const
{
    return mModel;
}

float Terrain::z() const
{
    return mZ;
}

float Terrain::x() const
{
    return mX;
}

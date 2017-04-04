#include "terrainshader.h"

#include <toolbox/maths.h>

TerrainShader::TerrainShader() :
    ShaderProgram(":/shaders/shaders/terrainShader.vert",
                  ":/shaders/shaders/terrainShader.frag")
{

}

void TerrainShader::loadTransformationMatrix(const QMatrix4x4 &matrix)
{
    loadMatrix(mLocationTransformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(const QMatrix4x4 &matrix)
{
    loadMatrix(mLocationProjectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(const CameraSharedPtr &camera)
{
    loadMatrix(mLocationViewMatrix, Maths::createViewMatrix(camera));
}

void TerrainShader::loadLight(const LightSharedPtr &light)
{
    loadVector(mLocationLightPosition, light->position());
    loadVector(mLocationLightColor, light->color());
}

void TerrainShader::loadShineVariables(const float &shineDamper, const float &reflectivity)
{
    loadFloat(mLocationShineDamper, shineDamper);
    loadFloat(mLocationReflectivity, reflectivity);
}

void TerrainShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}


void TerrainShader::getAllUniformLocations()
{
    mLocationTransformationMatrix = getUniformLocation("transformationMatrix");
    mLocationProjectionMatrix = getUniformLocation("projectionMatrix");
    mLocationViewMatrix = getUniformLocation("viewMatrix");
    mLocationLightPosition = getUniformLocation("lightPosition");
    mLocationLightColor = getUniformLocation("lightColor");
    mLocationReflectivity = getUniformLocation("reflectivity");
    mLocationShineDamper = getUniformLocation("shineDamper");

}

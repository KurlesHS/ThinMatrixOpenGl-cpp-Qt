#include "staticshader.h"

#include <toolbox/maths.h>

StaticShader::StaticShader(const QString &vertexFile, const QString &fragmentFile) :
    ShaderProgram(vertexFile, fragmentFile),
    mLocationTransformationMatrix(-1)
{

}

void StaticShader::loadTransformationMatrix(const QMatrix4x4 &matrix)
{
    loadMatrix(mLocationTransformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const QMatrix4x4 &matrix)
{
    loadMatrix(mLocationProjectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(const CameraSharedPtr &camera)
{
    loadMatrix(mLocationViewMatrix, Maths::createViewMatrix(camera));
}

void StaticShader::loadLight(const LightSharedPtr &light)
{
    loadVector(mLocationLightPosition, light->position());
    loadVector(mLocationLightColor, light->color());
}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}


void StaticShader::getAllUniformLocations()
{
    mLocationTransformationMatrix = getUniformLocation("transformationMatrix");
    mLocationProjectionMatrix = getUniformLocation("projectionMatrix");
    mLocationViewMatrix = getUniformLocation("viewMatrix");
    mLocationLightPosition = getUniformLocation("lightPosition");
    mLocationLightColor = getUniformLocation("lightColor");

}

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

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}


void StaticShader::getAllUniformLocations()
{
    mLocationTransformationMatrix = getUniformLocation("transformationMatrix");
    mLocationProjectionMatrix = getUniformLocation("projectionMatrix");
    mLocationViewMatrix = getUniformLocation("viewMatrix");
}

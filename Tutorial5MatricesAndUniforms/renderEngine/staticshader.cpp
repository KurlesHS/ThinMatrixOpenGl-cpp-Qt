#include "staticshader.h"

StaticShader::StaticShader(const QString &vertexFile, const QString &fragmentFile) :
    ShaderProgram(vertexFile, fragmentFile),
    mLocationTransformationMatrix(-1)
{

}


void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}


void StaticShader::getAllUniformLocations()
{
    mLocationTransformationMatrix = getUniformLocation("transformationMatrix");
}

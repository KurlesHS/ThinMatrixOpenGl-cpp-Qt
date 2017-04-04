#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "shaderprogram.h"
#include "entities/camera.h"

class StaticShader : public ShaderProgram
{
public:
    StaticShader(const QString &vertexFile, const QString &fragmentFile);

    void loadTransformationMatrix(const QMatrix4x4 &matrix);
    void loadProjectionMatrix(const QMatrix4x4 &matrix);
    void loadViewMatrix(const CameraSharedPtr &camera);


    // ShaderProgram interface
protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    GLint mLocationTransformationMatrix;
    GLint mLocationProjectionMatrix;
    GLint mLocationViewMatrix;
};

#endif // STATICSHADER_H

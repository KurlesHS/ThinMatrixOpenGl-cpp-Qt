#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "shaderprogram.h"

class StaticShader : public ShaderProgram
{
public:
    StaticShader(const QString &vertexFile, const QString &fragmentFile);


    // ShaderProgram interface
protected:
    virtual void bindAttributes() override;
};

#endif // STATICSHADER_H

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLFunctions_3_2_Core>
#include <QSharedPointer>

class ShaderProgram;

using ShaderProgramSharedPrt = QSharedPointer<ShaderProgram>;

class ShaderProgram : protected QOpenGLFunctions_3_2_Core
{
public:
    ShaderProgram(const QString &vertexFile, const QString &fragmentFile);
    ~ShaderProgram();

    void init();

    bool isValid() const;

    void start();
    void stop();

    void cleanUp();

    QString lastError() const;

protected:
    virtual void bindAttributes() = 0;

    void bindAttribute(GLuint attribute, const QString &variableName) ;

private:
    GLint loadShader(const QString &file, const GLenum type);


private:
    GLint mProgramId;
    GLint mFragmentShaderId;
    GLint mVertexShaderId;
    QString mLastError;
};

#endif // SHADERPROGRAM_H

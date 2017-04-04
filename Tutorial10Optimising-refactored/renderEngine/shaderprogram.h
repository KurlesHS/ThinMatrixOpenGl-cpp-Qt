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
    virtual void getAllUniformLocations() = 0;

    void bindAttribute(GLuint attribute, const QString &variableName) ;
    GLint getUniformLocation(const QString &uniformName);

    void loadFloat(const GLint &location, const GLfloat &value);
    void loadBoolean(const GLint &location, const bool &value);
    void loadVector(const GLint &location, const QVector3D &vector);
    void loadMatrix(const GLint &location, const QMatrix4x4 &matrix);


private:
    GLint loadShader(const QString &file, const GLenum type);


private:
    const QString mVertexFile;
    const QString mFragmentFile;
    GLint mProgramId;
    GLint mFragmentShaderId;
    GLint mVertexShaderId;
    QString mLastError;
};

#endif // SHADERPROGRAM_H

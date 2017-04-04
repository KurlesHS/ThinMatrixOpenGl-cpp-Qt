#include "shaderprogram.h"

#include <QFile>
#include <QDebug>
#include <QVector3D>
#include <QMatrix4x4>

ShaderProgram::ShaderProgram(const QString &vertexFile, const QString &fragmentFile) :
    mVertexFile(vertexFile),
    mFragmentFile(fragmentFile),
    mProgramId(-1),
    mFragmentShaderId(-1),
    mVertexShaderId(-1)
{
    initializeOpenGLFunctions();
}

ShaderProgram::~ShaderProgram()
{
    cleanUp();
}

void ShaderProgram::init()
{
    /* грузим вершинный шейдер (для каждой вершины) */
    mVertexShaderId = loadShader(mVertexFile, GL_VERTEX_SHADER);
    if (mVertexShaderId < 0) {
        return;
    }
    /* грузим фрагментный шейдер (для каждой точки) */
    mFragmentShaderId = loadShader(mFragmentFile, GL_FRAGMENT_SHADER);
    if (mFragmentShaderId < 0) {
        return;
    }

    /* создаем программу */
    mProgramId = glCreateProgram();
    /* аттачим к ней вершинный шейдер */
    glAttachShader(mProgramId, mVertexShaderId);
    /* и фрагментный шейдер */
    glAttachShader(mProgramId, mFragmentShaderId);
    /* привязываем атрибуты */
    if (isValid()) {
        bindAttributes();
    }
    /* линкуем */
    glLinkProgram(mProgramId);
    /* проверяем */

    GLint isLinked = 0;
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE) {
        char buff[0x0200];
        GLsizei len;
        glGetProgramInfoLog(mProgramId, sizeof(buff), &len, buff);
        mLastError = QObject::tr(R"(link error: %0)")
                .arg(QString::fromLatin1(buff, len));
        cleanUp();
        return;

    }
    glValidateProgram(mProgramId);
    getAllUniformLocations();

}

bool ShaderProgram::isValid() const
{
    return mProgramId >= 0;
}

void ShaderProgram::start()
{
    if (isValid()) {
        glUseProgram(mProgramId);
    }
}

void ShaderProgram::stop()
{
    if (isValid()) {
        glUseProgram(0);
    }
}

void ShaderProgram::cleanUp()
{
    stop();
    if (mProgramId >= 0) {
        glDetachShader(mProgramId, mVertexShaderId);
        glDetachShader(mProgramId, mFragmentShaderId);
        glDeleteProgram(mProgramId);
        mProgramId = -1;
    }

    if (mVertexShaderId >= 0) {
        glDeleteShader(mVertexShaderId);
        mVertexShaderId = -1;
    }

    if (mFragmentShaderId >= 0) {
        glDeleteShader(mFragmentShaderId);
        mFragmentShaderId = -1;
    }
}

void ShaderProgram::bindAttribute(GLuint attribute, const QString &variableName)
{
    if (mProgramId >= 0)  {
        glBindAttribLocation(mProgramId, attribute, variableName.toLatin1().data());
    }
}

GLint ShaderProgram::getUniformLocation(const QString &uniformName)
{
    GLint result = -1;
    if (isValid()) {
        result = glGetUniformLocation(mProgramId, uniformName.toLatin1().data());
    }
    return result;
}

void ShaderProgram::loadFloat(const GLint &location, const GLfloat &value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadBoolean(const GLint &location, const bool &value)
{
    glUniform1f(location, value ? 1 : 0);
}

void ShaderProgram::loadVector(const GLint &location, const QVector3D &vector)
{
    glUniform3f(location, vector.x(), vector.y(), vector.z());
}

void ShaderProgram::loadMatrix(const GLint &location, const QMatrix4x4 &matrix)
{
    glUniformMatrix4fv(location, 1, false, matrix.constData());
}



GLint ShaderProgram::loadShader(const QString &file, const GLenum type)
{
    mLastError.clear();
    GLint result = -1;

    QFile f(file);
    if (f.open(QIODevice::ReadOnly)) {
        QByteArray shaderData = f.readAll();
        f.close();
        GLuint shaderId = glCreateShader(type);
        GLchar *data = shaderData.data();
        glShaderSource(shaderId, 1, &data, 0);
        glCompileShader(shaderId);
        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            char buff[0x0200];
            GLsizei len;
            glGetShaderInfoLog(shaderId, sizeof(buff), &len, buff);
            mLastError = QObject::tr(R"(can't compile shader programm: %0)")
                    .arg(QString::fromLatin1(buff, len));
            glDeleteShader(shaderId);
        } else {
            result = shaderId;
        }
    } else {
        mLastError = QObject::tr(R"(can't load "%0")")
                .arg(file);
    }
    return result;
}

QString ShaderProgram::lastError() const
{
    return mLastError;
}

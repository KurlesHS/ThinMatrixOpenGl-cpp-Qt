#include "loader.h"

#include <QVector>
#include <QImage>

Loader::Loader()
{
    initializeOpenGLFunctions();
}

Loader::~Loader()
{
    cleanUp();
}

RawModelSharedPtr Loader::loadDataToVao(const QVector<GLfloat> &positions, const QVector<GLfloat> &textureCoords, const QVector<GLint> &indices)
{
    int vaoId = createVao();
    bindIndicesBuffer(indices);
    storeDataAttributeList(0, 3, positions);
    storeDataAttributeList(1, 2, textureCoords);
    unbindVao();
    return RawModelSharedPtr::create(vaoId, indices.size());
}

GLint Loader::loadTexture(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        return -1;
    }

    image = image.convertToFormat(QImage::Format_RGBA8888);
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.scanLine(0));
    glBindTexture(GL_TEXTURE_2D, 0);
    mTextures.append(texId);
    return texId;
}

void Loader::cleanUp()
{
    for (GLuint vbo : mVbos) {
        glDeleteBuffers(1, &vbo);
    }

    for (GLuint vao : mVaos) {
       glDeleteVertexArrays(1, &vao);
    }

    for (GLuint texture : mTextures) {
       glDeleteTextures(1, &texture);
    }
    mVaos.clear();
    mVbos.clear();
}

int Loader::createVao()
{
    /* создаём VAO - Vertex Array Object */
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    mVaos.append(vaoId);
    return vaoId;
}

void Loader::storeDataAttributeList(int attributeNumber, const int coordinateSize, const QVector<GLfloat> &data)
{
    /* создаеём VBO - Vertex Buffer Object */
    GLuint vboId;
    glGenBuffers(1, &vboId);
    mVbos.append(vboId);
    /* делаем его активным */
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    /* пихаем туда данные */
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    /* назначаем атрибут */
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
    /* анбинд буфера  VBO */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Loader::bindIndicesBuffer(const QVector<GLint> &indices)
{
    GLuint vboId;
    glGenBuffers(1, &vboId);
    mVbos.append(vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

}

void Loader::unbindVao()
{
    /* unbind VAO */
    glBindVertexArray(0);
}

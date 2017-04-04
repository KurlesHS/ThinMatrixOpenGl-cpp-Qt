#include "loader.h"

#include <QVector>

Loader::Loader()
{
    initializeOpenGLFunctions();
}

Loader::~Loader()
{
    cleanUp();
}

RawModelSharedPtr Loader::loadDataToVao(const QVector<GLfloat> &positions, const QVector<GLint> &indices)
{
    int vaoId = createVao();
    bindIndicesBuffer(indices);
    storeDataAttributeList(0, positions);
    unbindVao();
    return RawModelSharedPtr::create(vaoId, indices.size());
}

void Loader::cleanUp()
{
    for (GLuint vbo : mVbos) {
        glDeleteBuffers(1, &vbo);
    }

    for (GLuint vao : mVaos) {
       glDeleteVertexArrays(1, &vao);
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

void Loader::storeDataAttributeList(int attributeNumber, const QVector<GLfloat> &data)
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
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);
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

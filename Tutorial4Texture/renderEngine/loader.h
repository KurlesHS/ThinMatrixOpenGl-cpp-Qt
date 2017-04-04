#ifndef LOADER_H
#define LOADER_H

#include <QSharedPointer>
#include <QOpenGLFunctions_3_2_Core>

#include <QList>

#include <models/rawmodel.h>

class Loader : protected QOpenGLFunctions_3_2_Core
{
public:
    Loader();
    ~Loader();

    RawModelSharedPtr loadDataToVao(const QVector<GLfloat> &positions, const QVector<GLfloat> &textureCoords, const QVector<GLint> &indices);
    GLint loadTexture(const QString &fileName);

    void cleanUp();

private:
    int createVao();
    void storeDataAttributeList(int attributeNumber, const int coordinateSize, const QVector<GLfloat> &data);
    void bindIndicesBuffer(const QVector<GLint> &indices);
    void unbindVao();

private:
    QList<GLint> mVbos;
    QList<GLint> mVaos;
    QList<GLint> mTextures;


};

#endif // LOADER_H

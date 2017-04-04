#ifndef LOADER_H
#define LOADER_H

#include <QSharedPointer>
#include <QOpenGLFunctions_3_2_Core>

#include <QList>

#include "rawmodel.h"

class Loader : protected QOpenGLFunctions_3_2_Core
{
public:
    Loader();
    ~Loader();

    RawModelSharedPtr loadDataToVao(const QVector<GLfloat> &positions);
    void cleanUp();

private:
    int createVao();
    void storeDataAttributeList(int attributeNumber, const QVector<GLfloat> &data);
    void unbindVao();

private:
    QList<GLint> mVbos;
    QList<GLint> mVaos;


};

#endif // LOADER_H

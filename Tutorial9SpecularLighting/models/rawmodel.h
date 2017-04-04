#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <QSharedPointer>

class RawModel;

using RawModelSharedPtr = QSharedPointer<RawModel>;

class RawModel
{
public:
    RawModel(const int vaoId, const int vertexCount);

    int vaoId() const;
    int vertexCount() const;

private:
    const int mVaoId;
    const int mVertexCount;
};

#endif // RAWMODEL_H

#include "rawmodel.h"

RawModel::RawModel(const int vaoId, const int vertexCount) :
    mVaoId(vaoId),
    mVertexCount(vertexCount)
{

}

int RawModel::vaoId() const
{
    return mVaoId;
}

int RawModel::vertexCount() const
{
    return mVertexCount;
}

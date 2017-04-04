#include "texturedmodel.h"

TexturedModel::TexturedModel(const RawModelSharedPtr &model, const ModelTexture &texture) :
    mRawModel(model),
    mTexture(texture)
{

}

RawModelSharedPtr TexturedModel::rawModel() const
{
    return mRawModel;
}

ModelTexture TexturedModel::texture() const
{
    return mTexture;
}

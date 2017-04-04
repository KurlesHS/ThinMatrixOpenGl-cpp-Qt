#include "modeltexture.h"

ModelTexture::ModelTexture(const GLint textureId) :
    mTexureId(textureId)
{

}

GLint ModelTexture::textureId() const
{
    return mTexureId;
}

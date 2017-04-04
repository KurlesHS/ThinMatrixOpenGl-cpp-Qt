#include "modeltexture.h"

ModelTexture::ModelTexture(const GLint textureId) :
    mTexureId(textureId),
    mShineDamper(1),
    mReflectivity(0)
{

}

GLint ModelTexture::textureId() const
{
    return mTexureId;
}

GLfloat ModelTexture::shineDamper() const
{
    return mShineDamper;
}

void ModelTexture::setShineDamper(const GLfloat &shineDamper)
{
    mShineDamper = shineDamper;
}

GLfloat ModelTexture::reflectivity() const
{
    return mReflectivity;
}

void ModelTexture::setReflectivity(const GLfloat &reflectivity)
{
    mReflectivity = reflectivity;
}

#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <QtOpenGL>

class ModelTexture
{
public:
    ModelTexture(const GLint textureId);

    GLint textureId() const;

    GLfloat shineDamper() const;
    void setShineDamper(const GLfloat &shineDamper);

    GLfloat reflectivity() const;
    void setReflectivity(const GLfloat &reflectivity);

private:
    const GLint mTexureId;
    GLfloat mShineDamper;
    GLfloat mReflectivity;
};

#endif // MODELTEXTURE_H

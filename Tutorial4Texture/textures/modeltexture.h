#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <QtOpenGL>

class ModelTexture
{
public:
    ModelTexture(const GLint textureId);

    GLint textureId() const;

private:
    const GLint mTexureId;
};

#endif // MODELTEXTURE_H

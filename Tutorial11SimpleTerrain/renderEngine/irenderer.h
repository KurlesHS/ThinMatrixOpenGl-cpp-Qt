#ifndef IRENDERER_H
#define IRENDERER_H

#include <QOpenGLFunctions_3_2_Core>

class IRenderer : protected QOpenGLFunctions_3_2_Core
{
public:
    IRenderer();
    virtual ~IRenderer();

    virtual void render() = 0;

};

#endif // IRENDERER_H

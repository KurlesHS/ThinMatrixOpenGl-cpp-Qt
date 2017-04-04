#ifndef RENDERER_H
#define RENDERER_H

#include "irenderer.h"
#include "staticshader.h"

#include "rawmodel.h"

class Loader;

class Renderer : public IRenderer
{
public:
    Renderer();
    ~Renderer();

        // IRenderer interface
public:
    virtual void render() override;
    virtual void prepare() override;

    void render(RawModelSharedPtr model);

private:
    Loader *mLoader;
    StaticShader *mShader;
    RawModelSharedPtr mModel;

};

#endif // RENDERER_H

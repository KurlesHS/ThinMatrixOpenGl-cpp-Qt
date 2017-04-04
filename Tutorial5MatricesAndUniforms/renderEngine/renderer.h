#ifndef RENDERER_H
#define RENDERER_H

#include "irenderer.h"
#include "staticshader.h"

#include <models/rawmodel.h>
#include <models/texturedmodel.h>

class Loader;
class TexturedModel;

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
    void render(TexturedModelSharedPtr model);

private:
    Loader *mLoader;
    StaticShader *mShader;
    RawModelSharedPtr mModel;
    TexturedModelSharedPtr mTexturedModel;

};

#endif // RENDERER_H

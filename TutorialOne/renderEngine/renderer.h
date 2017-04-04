#ifndef RENDERER_H
#define RENDERER_H

#include "irenderer.h"

#include "rawmodel.h"

class Renderer : public IRenderer
{
public:
    Renderer(RawModelSharedPtr model);

        // IRenderer interface
public:
    virtual void render() override;
    virtual void prepare() override;

    void render(RawModelSharedPtr model);

private:
    RawModelSharedPtr mModel;
};

#endif // RENDERER_H

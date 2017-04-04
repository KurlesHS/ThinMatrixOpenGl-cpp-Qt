#ifndef RENDERER_H
#define RENDERER_H

#include "irenderer.h"
#include "staticshader.h"

#include <models/rawmodel.h>
#include <models/texturedmodel.h>

#include <entities/entity.h>

#include <QMatrix4x4>

#include <renderEngine/displaymanager.h>

class Loader;
class TexturedModel;

class Renderer : public IRenderer
{
public:
    static constexpr float FOV = 70;
    static constexpr float NearPlane = 0.1;
    static constexpr float FarPlane = 1000.;

    Renderer(DisplayManager *displayManager);
    ~Renderer();

        // IRenderer interface
public:
    virtual void render() override;
    virtual void prepare() override;

    void render(RawModelSharedPtr model);
    void render(TexturedModelSharedPtr model);
    void render(EntitySharedPtr entity, StaticShader *shader);

    void createProjectionMatrix();

private:
    DisplayManager *mDisplayManager;
    Loader *mLoader;
    StaticShader *mShader;
    RawModelSharedPtr mModel;
    TexturedModelSharedPtr mTexturedModel;
    EntitySharedPtr mEntity;
    QMatrix4x4 mProjectionMatrix;
    CameraSharedPtr mCamera;
    LightSharedPtr mLight;

};

#endif // RENDERER_H

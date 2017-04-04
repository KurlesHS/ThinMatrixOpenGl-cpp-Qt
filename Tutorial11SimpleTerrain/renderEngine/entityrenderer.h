#ifndef RENDERER_H
#define RENDERER_H

#include "staticshader.h"

#include <models/texturedmodel.h>
#include <entities/entity.h>

#include <QOpenGLFunctions_3_2_Core>
#include <QMatrix4x4>
#include <QHash>
#include <QList>


class Loader;
class TexturedModel;

class EntityRenderer : protected QOpenGLFunctions_3_2_Core
{
public:    
    EntityRenderer(StaticShader *shader, QMatrix4x4 projectionMatrix);
    ~EntityRenderer();

public:    
    void render(QHash<TexturedModelSharedPtr, QList<EntitySharedPtr>> entities);

private:
    void prepareTexturedModel(TexturedModelSharedPtr model);
    void unbindTexturedModel();
    void prepareInstance(EntitySharedPtr entity);    

private:    
    StaticShader *mShader;    
    QMatrix4x4 mProjectionMatrix;    


};

#endif // RENDERER_H

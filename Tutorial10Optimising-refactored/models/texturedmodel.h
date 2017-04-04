#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include <QSharedPointer>

#include "rawmodel.h"
#include <textures/modeltexture.h>

class TexturedModel;

using TexturedModelSharedPtr = QSharedPointer<TexturedModel>;

class TexturedModel
{
public:
    TexturedModel(const RawModelSharedPtr &model, const ModelTexture &texture);

    RawModelSharedPtr rawModel() const;

    ModelTexture texture() const;

private:
    RawModelSharedPtr mRawModel;
    ModelTexture mTexture;
};

#endif // TEXTUREDMODEL_H

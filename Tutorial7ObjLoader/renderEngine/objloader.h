#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <models/rawmodel.h>

#include "loader.h"

class ObjLoader
{
public:
    ObjLoader();

    static RawModelSharedPtr loadObjModel(const QString &fileName, Loader *loader);
};

#endif // OBJLOADER_H

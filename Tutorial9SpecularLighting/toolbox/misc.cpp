#include "misc.h"

Misc::Misc()
{

}

QString Misc::resourceFilePath(const QString &path)
{
    return SRCDIR + path;
}

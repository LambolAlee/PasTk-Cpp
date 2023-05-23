#include "defaultsettings.h"


const QString defaults::getQString(std::string_view str)
{
    return QString(str.data());
}

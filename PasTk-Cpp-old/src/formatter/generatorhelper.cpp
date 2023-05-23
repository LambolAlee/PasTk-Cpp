#include "generatorhelper.h"

#include <QXmlStreamAttributes>


const QString GeneratorHelper::dataTag()
{
    return QLatin1String("data");
}

QString GeneratorHelper::readAttr(const QXmlStreamAttributes &attrs, const QString &attrName, const QString &defaultValue)
{
    if (attrs.hasAttribute(attrName))
        return attrs.value(attrName).toString();
    else
        return defaultValue;
}

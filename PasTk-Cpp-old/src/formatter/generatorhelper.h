#ifndef GENERATORHELPER_H
#define GENERATORHELPER_H

#include <QDir>

class QXmlStreamAttributes;

namespace GeneratorHelper
{
    const QString dataTag();
    QString readAttr(const QXmlStreamAttributes &attrs, const QString &attrName, const QString &defaultValue);
};

#endif // GENERATORHELPER_H

#include "templatehelper.h"


const QStringList TemplateHelper::getTemplatesNames() const
{
    return keys();
}

const QString TemplateHelper::getTemplate(const QString &name) const
{
    return value(name);
}

void TemplateHelper::setTemplate(const QString &name, const QString &templateString)
{
    insert(name, templateString);
    _modified = true;
}

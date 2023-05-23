#include "templatehelper.h"


TemplateHelper::TemplateHelper() {}
TemplateHelper::~TemplateHelper() {}

const QStringList TemplateHelper::getTemplatesNames() const
{
    return keys();
}

const TemplateContent TemplateHelper::getTemplate(const QString &name) const
{
    return value(name);
}

void TemplateHelper::setTemplate(const QString &name, const QString &templateString, const QString &description)
{
    setTemplate(name, {templateString, description});
}

void TemplateHelper::setTemplate(const QString &name, TemplateContent content)
{
    insert(name, content);
    setModified(true);
}

const QPair<QString, TemplateContent> TemplateHelper::firstTemplate()
{
    if (isEmpty()) return {};
    auto pair = constKeyValueBegin();
    return {pair->first, pair->second};
}

void TemplateHelper::removeTemplate(const QString &name)
{
    remove(name);
    setModified(true);
}

void TemplateHelper::renameTemplate(const QString &oldName, const QString &newName)
{
    auto content = getTemplate(oldName);
    remove(oldName);
    setTemplate(newName, content);
}

#include "templatehelper.h"


TemplateHelper::TemplateHelper() {}
TemplateHelper::~TemplateHelper() {}

const QStringList TemplateHelper::getTemplateNameList() const
{
    return keys();
}

const QString TemplateHelper::getTemplateStringByName(const QString &name) const
{
    return value(name);
}

const TemplatePair TemplateHelper::getTemplate(const QString &name) const
{
    return {name, getTemplateStringByName(name)};
}

void TemplateHelper::setTemplate(const QString &name, const QString &templateString)
{
    insert(name, templateString);
    setModified(true);
}

void TemplateHelper::setTemplate(const TemplatePair &pair)
{
    insert(pair.first, pair.second);
    setModified(true);
}

const TemplatePair TemplateHelper::firstTemplate()
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
    auto content = getTemplateStringByName(oldName);
    remove(oldName);
    setTemplate(newName, content);
}

#ifndef TEMPLATEHELPER_H
#define TEMPLATEHELPER_H

#include <QMap>
#include "src/utils/Singleton.h"


using Templates = QMap<QString, QString>;   // {template_name, template_string}
using TemplatePair = QPair<QString, QString>;    // {template_name, template_string}

class TemplateHelper : private Templates
{
    SINGLETON(TemplateHelper)
public:
    const QStringList getTemplateNameList() const;
    const QString getTemplateStringByName(const QString &name) const;
    const TemplatePair getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString);
    void setTemplate(const TemplatePair &pair);
    const TemplatePair firstTemplate();
    void removeTemplate(const QString &name);
    void renameTemplate(const QString &oldName, const QString &newName);

    using Templates::keyValueBegin;
    using Templates::keyValueEnd;
    using Templates::constKeyValueBegin;
    using Templates::constKeyValueEnd;
    using Templates::contains;
    using Templates::count;
    using Templates::clear;

    bool isModified() { return _modified; }
    void setModified(bool state) { _modified = state; }

private:
    bool _modified = false;
};

#endif // TEMPLATEHELPER_H

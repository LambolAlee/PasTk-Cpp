#ifndef TEMPLATEHELPER_H
#define TEMPLATEHELPER_H

#include <QMap>
#include "src/utils/Singleton.h"


using TemplateContent = QPair<QString, QString>;
using Templates = QMap<QString, TemplateContent>;

class TemplateHelper : private Templates
{
    SINGLETON(TemplateHelper)
public:
    const QStringList getTemplatesNames() const;
    const TemplateContent getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString, const QString &description);
    void setTemplate(const QString &name, TemplateContent content);
    const QPair<QString, TemplateContent> firstTemplate();
    void removeTemplate(const QString &name);
    void renameTemplate(const QString &oldName, const QString &newName);

    using Templates::keyValueBegin;
    using Templates::keyValueEnd;
    using Templates::constKeyValueBegin;
    using Templates::constKeyValueEnd;
    using Templates::contains;

    bool isModified() { return _modified; }
    void setModified(bool state) { _modified = state; }

private:
    bool _modified = false;
};

#endif // TEMPLATEHELPER_H

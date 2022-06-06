#ifndef TEMPLATEHELPER_H
#define TEMPLATEHELPER_H

#include <QMap>


using Templates = QMap<QString, QString>;

class TemplateHelper : private Templates
{
public:
    const Templates &templates() const;

    const QStringList getTemplatesNames() const;
    const QString getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString);

    using Templates::keyValueBegin;
    using Templates::keyValueEnd;
};

#endif // TEMPLATEHELPER_H

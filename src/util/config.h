#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

#include "Singleton.h"
#include "formatter/templatehelper.h"


class Config : private QSettings
{
    Q_OBJECT
    SINGLETON(Config)

public:
// Template edit area
    const Templates &templates() const;
    const QStringList getTemplatesNames() const;
    const QString getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString);

private:
    TemplateHelper _templateHelper;
    void loadTemplates();
    void saveTemplates();
};

#endif // CONFIG_H

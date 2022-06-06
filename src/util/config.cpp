#include "config.h"

#include <QApplication>

Config::Config()
    : QSettings(qApp->applicationDirPath().append("/config.ini"), QSettings::IniFormat)
{
    loadTemplates();
}

Config::~Config()
{
    saveTemplates();
}

const Templates &Config::templates() const
{
    return _templateHelper.templates();
}

const QStringList Config::getTemplatesNames() const
{
    return _templateHelper.getTemplatesNames();
}

const QString Config::getTemplate(const QString &name) const
{
    return _templateHelper.getTemplate(name);
}

void Config::setTemplate(const QString &name, const QString &templateString)
{
    _templateHelper.setTemplate(name, templateString);
}

void Config::loadTemplates()
{
    int size = beginReadArray("Templates");
    for (int i = 0; i < size; ++i) {
        setArrayIndex(i);
        _templateHelper.setTemplate(value("name").toString(), value("template").toString());
    }
    endArray();
}

void Config::saveTemplates()
{
    int i = 0;

    beginWriteArray("Templates");
    for (auto pair = _templateHelper.keyValueBegin(); pair != _templateHelper.keyValueEnd(); ++pair) {
        setArrayIndex(i++);
        setValue("name", pair->first);
        setValue("template", pair->second);
    }
    endArray();
}

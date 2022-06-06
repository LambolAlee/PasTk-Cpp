#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "generatorinterface.h"
#include "util/Singleton.h"

#include <QDir>


class QPluginLoader;
class PluginManagerPrivate;
class Processor;

class PluginManager
{
    SINGLETON(PluginManager)
public:
    void loadAll();
    void unloadAll();

    void scan(const QString &path);
    void load(const QString &path);
    void unload(const QString &path);

    Processor *pluginsProcessor();
    QList<QPluginLoader *> plugins();

private:
    PluginManagerPrivate *d;
    QDir _pluginDir;
    Processor *_processor = nullptr;
};

#endif // PLUGINMANAGER_H

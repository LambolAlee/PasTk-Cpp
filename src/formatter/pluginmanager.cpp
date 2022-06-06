#include "pluginmanager.h"

#include <QLibrary>
#include <QApplication>
#include <QPluginLoader>

#include "processor.h"


/******** PluginManagerPrivate *********/
class PluginManagerPrivate
{
public:
    QHash<QString, QVariant> _names;
    QHash<QString, QVariant> _versions;
    QHash<QString, QPluginLoader *> _loaders;
};
/******** PluginManagerPrivate *********/


PluginManager::PluginManager()
{
    d = new PluginManagerPrivate;
    _pluginDir = QDir(qApp->applicationDirPath());
    _pluginDir.cdUp();
    _pluginDir.cd(QLatin1String("plugins"));
}

PluginManager::~PluginManager()
{
    delete d;
    delete _processor;
}

void PluginManager::loadAll()
{   
    for (QFileInfo info: _pluginDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        scan(info.absoluteFilePath());

    for (QFileInfo info: _pluginDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        load(info.absoluteFilePath());
}

void PluginManager::unloadAll()
{
    for(auto &&loader: d->_loaders)
        unload(d->_loaders.key(loader));
}

void PluginManager::scan(const QString &path)
{
    if (!QLibrary::isLibrary(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    d->_names.insert(path, json.value("name").toVariant());
    d->_versions.insert(path, json.value("version").toVariant());

    delete loader;
    loader = nullptr;
}

void PluginManager::load(const QString &path)
{
    if (!QLibrary::isLibrary(path))
        return;

    auto confDir = QDir(_pluginDir);
    confDir.cd(QLatin1String("conf"));

    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load()) {
        IGenerator *plugin = qobject_cast<IGenerator *>(loader->instance());
        if (plugin) {
            plugin->setConfDir(confDir);
            d->_loaders.insert(path, loader);
        } else {
            delete loader;
            loader = nullptr;
        }
    }
}

void PluginManager::unload(const QString &path)
{
    QPluginLoader *loader = d->_loaders.value(path);
    if (loader->unload()) {
        d->_loaders.remove(path);
        delete loader;
        loader = nullptr;
    }
}

Processor *PluginManager::pluginsProcessor()
{
    if (!_processor) _processor = new Processor(plugins());
    return _processor;
}

QList<QPluginLoader *> PluginManager::plugins()
{
    return d->_loaders.values();
}

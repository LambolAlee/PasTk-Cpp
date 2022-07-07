#include "pluginmanager.h"

#include <QApplication>
#include <QPluginLoader>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QJsonDocument>

#include "processor.h"
#include "pluginmodel.h"


/******** PluginManagerPrivate *********/
class PluginManagerPrivate
{
public:
    QHash<QString, QPluginLoader *> _loaders;
    QList<QString> _enabled;
    QList<QString> _disabled;
};
/******** PluginManagerPrivate *********/


const QString PluginManager::disabledFlag = ".disabled";
const QString PluginManager::configName = "plugins.json";

PluginManager::PluginManager()
{
    d = new PluginManagerPrivate;
    _pluginDir = QDir(qApp->applicationDirPath());
    _pluginDir.cdUp();
    _pluginDir.cd(QLatin1String("plugins"));

    if (!checkPluginsConfig())
        createPluginsConfig();

    connect(qApp, &QApplication::aboutToQuit, this, &PluginManager::updatePluginsConfig);

    loadAll();
}

PluginManager::~PluginManager()
{
    delete d;
    delete _processor;
    delete _model;
}

void PluginManager::loadAll()
{
    QFile config(_pluginDir.absoluteFilePath(configName));
    config.open(QIODevice::ReadOnly);
    auto data = config.readAll();
    config.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "[PluginManager] read plugins.json failed";
        return;
    }
    QJsonObject root = doc.object();
    auto enabledList = root.value("enabled").toArray();
    auto disabledList = root.value("disabled").toArray();

    QString path;
    for (auto &&fname: enabledList) {
        path = _pluginDir.absoluteFilePath(fname.toString());
        d->_enabled.append(path);
        scan(path);
    }
    for (auto &&fname: disabledList) {
        path = _pluginDir.absoluteFilePath(fname.toString());
        d->_disabled.append(path);
        scan(path);
    }

    for (auto &&fname: d->_enabled)
        load(fname);
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

    // QPluginLoader *loader = new QPluginLoader(path);
    // QJsonObject json = loader->metaData().value("MetaData").toObject();

    // handle dependencies here...

    // delete loader;
    // loader = nullptr;
}

void PluginManager::load(const QString &path)
{
    if (!QLibrary::isLibrary(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load()) {
        IGenerator *plugin = qobject_cast<IGenerator *>(loader->instance());
        if (plugin) {
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

void PluginManager::setEnabled(const QString &path, bool enabled)
{
    if (enabled == true && d->_disabled.contains(path)) {
        d->_enabled.append(path);
        d->_disabled.removeOne(path);
    } else if (enabled == false && d->_enabled.contains(path)) {
        d->_disabled.append(path);
        d->_enabled.removeOne(path);
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

QStandardItemModel *PluginManager::model()
{
    if (!_model) {
        _model = new PluginModel;
        _model->init(&d->_enabled, &d->_disabled);
    }
    return _model;
}

PluginInfo PluginManager::getInfoOf(const QString &path)
{
    PluginInfo info;
    QPluginLoader *loader = new QPluginLoader(path);
    auto data = loader->metaData().value("MetaData").toObject();
    info.path = path;
    info.name = data.value("name").toString();
    info.version = data.value("version").toString();
    info.author = data.value("author").toString();
    info.url = data.value("url").toString();
    info.description = data.value("description").toString();
    delete loader;
    return info;
}

bool PluginManager::checkPluginsConfig()
{
    return _pluginDir.exists(configName);
}

void PluginManager::createPluginsConfig()
{
    QJsonObject root;
    QJsonArray enabledList;
    QJsonArray disabledList;

    for (QFileInfo info: _pluginDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        if (QLibrary::isLibrary(info.absoluteFilePath())) {
            disabledList.append(QJsonValue(info.absoluteFilePath()));
        }
    }

    root.insert("enabled", enabledList);
    root.insert("disabled", disabledList);

    save2File(root);
}

void PluginManager::updatePluginsConfig()
{
    qDebug() << "[PluginManager] saving plugins config file...";
    QJsonObject root;
    QJsonArray enabledList;
    QJsonArray disabledList;

    for (auto &&path: d->_enabled)
        enabledList.append(QJsonValue(path));
    for (auto &&path: d->_disabled)
        disabledList.append(QJsonValue(path));

    root.insert("enabled", enabledList);
    root.insert("disabled", disabledList);

    save2File(root);
}

bool PluginManager::isDisabled(const QString &path)
{
    return d->_disabled.contains(path);
}

void PluginManager::save2File(const QJsonObject &root)
{
    QFile config(_pluginDir.absoluteFilePath(configName));
    bool ok = config.open(QIODevice::WriteOnly);
    if (ok) {
        QJsonDocument doc(root);
        config.write(doc.toJson());
        config.close();
    } else {
        qDebug() << "[PluginManager] write plugins.json failed";
    }
}

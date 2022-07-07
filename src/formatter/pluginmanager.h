#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "generatorinterface.h"
#include "util/Singleton.h"

#include <QDir>


class QPluginLoader;
class PluginManagerPrivate;
class Processor;
class QStandardItemModel;
class PluginModel;


struct PluginInfo {
    QString path;
    QString name;
    QString version;
    QString author;
    QString url;
    QString description;
};

class PluginManager : public QObject
{
    Q_OBJECT
    SINGLETON(PluginManager)
public:
    void loadAll();
    void unloadAll();

    void scan(const QString &path);
    void load(const QString &path);
    void unload(const QString &path);

    void setEnabled(const QString &path, bool enabled = true);

    Processor *pluginsProcessor();
    QList<QPluginLoader *> plugins();

    QStandardItemModel *model();

    PluginInfo getInfoOf(const QString &path);

private:
    bool checkPluginsConfig();
    bool isDisabled(const QString &path);
    void save2File(const QJsonObject &root);
    void createPluginsConfig();

private slots:
    void updatePluginsConfig();

private:
    static const QString disabledFlag;
    static const QString configName;
    PluginManagerPrivate *d;
    QDir _pluginDir;
    Processor *_processor = nullptr;
    PluginModel *_model = nullptr;
};

#endif // PLUGINMANAGER_H

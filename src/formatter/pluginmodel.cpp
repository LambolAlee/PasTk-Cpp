#include "pluginmodel.h"

#include <QPluginLoader>


PluginModel::PluginModel(QObject *parent)
    : QStandardItemModel{parent}
{
    setHorizontalHeaderLabels({"Name", "Load", "Version", "Author"});
}

void PluginModel::init(QStringList *enabledList, QStringList *disabledList)
{
    _enabled = enabledList;
    _disabled = disabledList;
    loadRowData(*_enabled, true);
    loadRowData(*_disabled, false);
}

void PluginModel::appandRowWithData(const QJsonObject &data, bool enabledFlag, const QString &path)
{
    QStandardItem *name = new QStandardItem(data.value("name").toString());
    QStandardItem *load = new QStandardItem(QString(20, ' '));
    load->setCheckable(true);
    load->setData(path);
    if (enabledFlag)
        load->setCheckState(Qt::Checked);
    else
        load->setCheckState(Qt::Unchecked);
    QStandardItem *version = new QStandardItem(data.value("version").toString());
    QStandardItem *author = new QStandardItem(data.value("author").toString());
    appendRow({name, load, version, author});
}

void PluginModel::loadRowData(const QStringList &list, bool enabledFlag)
{
    QPluginLoader *loader;
    for (auto &&path: list) {
        loader = new QPluginLoader(path);
        auto data = loader->metaData().value("MetaData").toObject();
        appandRowWithData(data, enabledFlag, path);
        delete loader;
        loader = nullptr;
    }
}

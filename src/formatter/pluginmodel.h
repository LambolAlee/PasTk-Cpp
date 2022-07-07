#ifndef PLUGINMODEL_H
#define PLUGINMODEL_H

#include <QStandardItemModel>


class PluginModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit PluginModel(QObject *parent = nullptr);

    void init(QStringList *enabledList, QStringList *disabledList);

private:
    void appandRowWithData(const QJsonObject &data, bool enabledFlag, const QString &path);
    void loadRowData(const QStringList &list, bool enabledFlag);

private:
    QStringList *_enabled;
    QStringList *_disabled;
};

#endif // PLUGINMODEL_H

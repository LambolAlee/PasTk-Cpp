#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QStandardItemModel>

#include "util/Singleton.h"


class DataManager : private QStandardItemModel
{
    Q_OBJECT
    SINGLETON(DataManager)

public:
    QStandardItemModel *model() { return this; }

    void insert(const QString &data);

    void setItem(const QModelIndex &index, const QString &data);

    void remove(int index);
    void remove(const QModelIndex &index);
    void remove(const QModelIndexList &idxList);

    void clear();

    int count();
};

#endif // DATAMANAGER_H

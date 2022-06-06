#include "datamanager.h"

DataManager::DataManager(): QStandardItemModel() {}
DataManager::~DataManager() {}

void DataManager::insert(const QString &data)
{
    appendRow(new QStandardItem(data));
}

void DataManager::setItem(const QModelIndex &index, const QString &data)
{
    setData(index, data);
}

void DataManager::remove(int index)
{
    removeRow(index);
}

void DataManager::remove(const QModelIndex &index)
{
    removeRow(index.row());
}

void DataManager::remove(const QModelIndexList &idxList)
{
    for (auto &&idx = idxList.crbegin(); idx < idxList.crend(); ++idx)
        removeRow(idx->row());
}

QStandardItem *DataManager::getItem(int row)
{
    return item(row);
}

void DataManager::clear()
{
    QStandardItemModel::clear();
}

int DataManager::count()
{
    return QStandardItemModel::rowCount();
}

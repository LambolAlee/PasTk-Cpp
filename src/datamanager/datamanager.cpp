#include "datamanager.h"

DataManager::DataManager(): QStandardItemModel() {}
DataManager::~DataManager() {}

void DataManager::insert(const QString &data)
{
    appendRow(new QStandardItem(data));
}

void DataManager::remove(int index)
{
    removeRow(index);
}

void DataManager::remove(const QModelIndex &index)
{
    removeRow(index.row());
}

void DataManager::clear()
{
    QStandardItemModel::clear();
}

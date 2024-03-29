
#include "datamanager.h"
#include <algorithm>

DataManager::DataManager()
{
    m_state = ModelState::Normal;
    connect(&m_listener, &ClipboardListener::newDataOccurred, this, &DataManager::push);
}

DataManager::~DataManager() {}

void DataManager::push(const QString &text)
{
    appendRow(new QStandardItem(text));
    emit itemCountChange(rowCount());
}

void DataManager::insert(int row, const QString &text)
{
    insertRow(row, new QStandardItem(text));
    emit itemCountChange(rowCount());
}

void DataManager::remove(const QModelIndexList &indexs)
{
    auto tmp = indexs.toList();
    std::sort(tmp.begin(), tmp.end(), [](const QModelIndex &i1, const QModelIndex &i2){ return i1.row() > i2.row(); });
    for (auto &&index = tmp.cbegin(); index != tmp.cend(); index++)
        removeRow(index->row());

    emit itemCountChange(rowCount());
}

void DataManager::remove(const QModelIndex &index)
{
    removeRow(index.row());
    emit itemCountChange(rowCount());
}

void DataManager::clearAll()
{
    clear();
    emit itemCountChange(0);
}

void DataManager::listen()
{
    m_listener.listen();
}

void DataManager::stop()
{
    m_listener.stop();
}

void DataManager::castFrom(int index)
{
    m_caster.setCurrent(index);
}

void DataManager::next()
{
    m_caster.next();
}

bool DataManager::isEnd()
{
    return m_caster.current() >= rowCount();
}

QString DataManager::castCurrent()
{
    return castAt(m_caster.current());
}

QString DataManager::castAt(int index)
{
    if (index >= 0 && index < rowCount())
        return item(index)->text();
    else
        return QString();
}

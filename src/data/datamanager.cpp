
#include "datamanager.h"

DataManager::DataManager()
{
    connect(&m_listener, &ClipboardListener::newDataOccurred, this, &DataManager::push);
}

DataManager::~DataManager() {}

void DataManager::push(const QString &text)
{
    if (!text.isEmpty())
        appendRow(new QStandardItem(text));
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


#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QStandardItemModel>
#include "src/utils/Singleton.h"
#include "clipboardlistener.h"
#include "datacaster.h"

class DataManager : public QStandardItemModel
{
    SINGLETON(DataManager)
public:
    void push(const QString &text);

    void listen();
    void stop();

    void castFrom(int index = 0);
    void next();
    QString castCurrent();
    QString castAt(int index);

private:
    ClipboardListener m_listener;
    DataCaster m_caster;
};

#endif // DATAMANAGER_H

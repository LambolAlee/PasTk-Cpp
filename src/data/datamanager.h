
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QStandardItemModel>
#include "src/utils/Singleton.h"
#include "clipboardlistener.h"
#include "datacaster.h"

enum ModelState {
    Normal,
    Copy,
};

class DataManager : public QStandardItemModel
{
    Q_OBJECT
    SINGLETON(DataManager)

public:
    void push(const QString &text);
    void insert(int row, const QString &text);
    void remove(const QModelIndexList &indexs);
    void remove(const QModelIndex &index);
    void clearAll();

    void startCopy() { m_state = ModelState::Copy; };
    void listen();
    void stop();
    bool isStopped() { return m_state == ModelState::Normal; };
    void endCopy() { m_state = ModelState::Normal; };

    void castFrom(int index);
    void next();
    bool isEnd();
    int currentIndex() { return m_caster.current(); };
    QString castCurrent();
    QString castAt(int index);

signals:
    void itemCountChange(int);

private:
    ClipboardListener m_listener;
    DataCaster m_caster;
    ModelState m_state;
};

#endif // DATAMANAGER_H

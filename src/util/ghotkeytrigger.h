#ifndef GHOTKEYTRIGGER_H
#define GHOTKEYTRIGGER_H

#include <QMap>
#include <QHotkey>

#include "Singleton.h"


class GHotkeyTrigger : public QObject, private QMap<QString, QHotkey*>
{
    Q_OBJECT
    SINGLETON(GHotkeyTrigger)

public:
    using QMap::value;
    void setHotkey(const QString &name, const QKeySequence &sequence);
    void update(const QString &name, const QKeySequence &sequence);

signals:
    void updateShortcutsSig();

private slots:
    void updateShortcuts();

private:
    void connectSignalsWithSlots();
};

#endif // GHOTKEYTRIGGER_H

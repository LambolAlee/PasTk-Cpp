#ifndef CFRAMELESSBRIDGE_H
#define CFRAMELESSBRIDGE_H

#include "Singleton.h"

#include <QObject>

class CFramelessBridge : public QObject
{
    Q_OBJECT
    SINGLETON(CFramelessBridge)

signals:
    void altKeyTriggered();
    void minimized();
    void closed();
    void topmost(bool);

    void hideForPaste(bool);

public:
    void emitAltKeyTriggered();
    void emitMinimized();
    void emitClosed();
    void emitTopmost(bool state);

    void emitHideForPaste(bool state);
};

#endif // CFRAMELESSBRIDGE_H

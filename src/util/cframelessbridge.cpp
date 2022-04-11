#include "cframelessbridge.h"

CFramelessBridge::CFramelessBridge() {}
CFramelessBridge::~CFramelessBridge() {}

void CFramelessBridge::emitAltKeyTriggered()
{
    emit altKeyTriggered();
}

void CFramelessBridge::emitMinimized()
{
    emit minimized();
}

void CFramelessBridge::emitClosed()
{
    emit closed();
}

void CFramelessBridge::emitTopmost(bool state)
{
    emit topmost(state);
}

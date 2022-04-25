#include "pasteutil.h"

#include "cframelessbridge.h"

#include <windows.h>
#include <QClipboard>
#include <QTimer>

#define VK_V 0x56


PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste(const QString &str)
{
    _clipBoard->setText(str);
    paste();
}

void PasteUtil::paste(bool directly)
{
    if (!directly)
        CFramelessBridge::instance().emitHideForPaste(true);
    QTimer::singleShot(100, this, &PasteUtil::_paste);
}

void PasteUtil::_paste() const
{
    keybd_event(VK_CONTROL, 0,0,0);
    keybd_event(VK_V, 0,0,0);
    keybd_event(VK_V, 0,2,0);
    keybd_event(VK_CONTROL, 0,2,0);

    CFramelessBridge::instance().emitHideForPaste(false);
}
#undef VK_V

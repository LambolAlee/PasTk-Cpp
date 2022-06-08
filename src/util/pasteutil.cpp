#include "pasteutil.h"

#include "cframelessbridge.h"

#include <windows.h>
#include <QClipboard>
#include <QTimer>

#define VK_V 0x56


PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste(const QString &str, bool directly)
{
    _clipBoard->setText(str);
    paste(directly);
}

void PasteUtil::paste(bool directly, bool needQuickPaste)
{
    if (!directly)
        CFramelessBridge::instance().emitHideForPaste(true);
    QTimer::singleShot(220, this, [=]{
        _paste();
        if (!directly)
            CFramelessBridge::instance().emitHideForPaste(false);
        if (needQuickPaste)
            _clipBoard->blockSignals(false);
    });
}

void PasteUtil::quickPaste(const QString &str)
{
    // used for pasting when on listening to the clipboard in home window
    _clipBoard->blockSignals(true);
    _clipBoard->setText(str);
    paste(false, true);
}

void PasteUtil::_paste() const
{
    keybd_event(VK_CONTROL, 0,0,0);
    keybd_event(VK_V, 0,0,0);
    keybd_event(VK_V, 0,2,0);
    keybd_event(VK_CONTROL, 0,2,0);
}
#undef VK_V

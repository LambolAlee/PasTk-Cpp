#include "pasteutil.h"

#include <windows.h>
#include <QClipboard>

#define VK_V 0x56

PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste(const QString &str)
{
    _clipBoard->setText(str);
    paste();
}

void PasteUtil::paste()
{
    keybd_event(VK_CONTROL, 0,0,0);
    keybd_event(VK_V, 0,0,0);
    keybd_event(VK_V, 0,2,0);
    keybd_event(VK_CONTROL, 0,2,0);
}

#include "pasteutil.h"

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <windows.h>

#define VK_V 0x56


PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste(QWidget *window)
{
    window->hide();
    QThread::msleep(300);
    execute_paste();
    window->show();
}

void PasteUtil::paste()
{
    execute_paste();
}

void PasteUtil::execute_paste()
{
    keybd_event(VK_CONTROL, 0,0,0);
    keybd_event(VK_V, 0,0,0);
    QThread::msleep(200);
    keybd_event(VK_V, 0,2,0);
    keybd_event(VK_CONTROL, 0,2,0);
}

bool PasteUtil::copy(const QString &text)
{
    if (!OpenClipboard(NULL)) {
        // Failed to open clipboard
        return false;
    }

    if (!EmptyClipboard()) {
        // Failed to clear clipboard
        CloseClipboard();
        return false;
    }

    // Calculate the size needed for the string, including null-terminator
    int textLength = text.size() +1;

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, textLength);
    if (!hMem) {
        // Memory allocation failed
        CloseClipboard();
        return false;
    }

    char* pMem = static_cast<char*>(GlobalLock(hMem));
    if (!pMem) {
        // Memory locking failed
        GlobalFree(hMem);
        CloseClipboard();
        return false;
    }
    strcpy_s(pMem, textLength, text.toUtf8().constData());
    GlobalUnlock(hMem);

    if (!SetClipboardData(CF_TEXT, hMem)) {
        // Failed to set clipboard data
        GlobalFree(hMem);
        CloseClipboard();
        return false;
    }

    GlobalFree(hMem);
    CloseClipboard();
    return true;
}

#undef VK_V

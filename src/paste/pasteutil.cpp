#include "pasteutil.h"

#include <windows.h>
#include <QWidget>
#include <QTimer>
#include <QThread>

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

    // TODO: convert the QString to const char*
    // QString.constData, QString.size() can get the correct length of a QString, not attempt to get the length using len(const QChar*)
    const char* text = "Hello, clipboard!";
    int textLength = strlen(text) + 1;

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

    strcpy_s(pMem, textLength, text);
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

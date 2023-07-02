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

#undef VK_V

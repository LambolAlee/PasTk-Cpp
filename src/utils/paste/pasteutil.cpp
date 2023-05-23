#include "pasteutil.h"

#include <windows.h>
#include <QWidget>
#include <QTimer>

#define VK_V 0x56


PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste([[maybe_unused]] QWidget *window)
{
    window->hide();
    QTimer::singleShot(300, this, [=]{
        execute_paste();
        window->show();
    });
}

void PasteUtil::execute_paste()
{
    keybd_event(VK_VONTROL, 0,0,0);
    keybd_event(VK_V, 0,0,0);
    QTimer::singleShot(200, this, [=]{
        keybd_event(VK_V, 0,2,0);
        keybd_event(VK_CONTROL, 0,2,0);
    });
}

#undef VK_V

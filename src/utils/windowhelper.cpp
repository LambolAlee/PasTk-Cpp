
#include "windowhelper.h"
#include <QWidget>
#include <QWindow>

#ifdef Q_OS_WIN
#include <windows.h>

void WindowHelper::setWindowUnfocusable(QWidget *widget, bool need_unfocus)
{
    HWND hWnd = (HWND)widget->winId();
    LONG exs = GetWindowLong(hWnd, GWL_EXSTYLE);

    if (need_unfocus) {
        // set the widget to be unfocusable
        setTopmost(widget, true);
        SetWindowLong(hWnd, GWL_EXSTYLE, exs | WS_EX_NOACTIVATE | WS_EX_COMPOSITED);
    } else {
        // restore the widget to be focusable
        SetWindowLong(hWnd, GWL_EXSTYLE, exs & ~WS_EX_NOACTIVATE & ~WS_EX_COMPOSITED);
        SetForegroundWindow(hWnd);
    }
}
#endif

void WindowHelper::setTopmost(QWidget *widget, bool need_topmost)
{
    QWindow *window = widget->windowHandle();
    window->setFlag(Qt::WindowStaysOnTopHint, need_topmost);
}

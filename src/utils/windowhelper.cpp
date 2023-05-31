
#include "windowhelper.h"
#include <QWidget>
#include <QWindow>

#ifdef Q_OS_WIN
#include <windows.h>

void WindowHelper::setWindowUnfocusable(QWidget *widget, bool need_unfocus)
{
    bool unfocus = widget->property("unfocus").toBool();

    HWND hWnd = (HWND)widget->winId();
    LONG exs = GetWindowLong(hWnd, GWL_EXSTYLE);

    if (need_unfocus && !unfocus) {
        // set the widget to be unfocusable
        if (!widget->property("topmost").toBool()) {
            setTopmost(widget, true);
        }
        widget->setProperty("unfocus", true);
        SetWindowLong(hWnd, GWL_EXSTYLE, exs | WS_EX_NOACTIVATE | WS_EX_COMPOSITED);
    } else if (!need_unfocus && unfocus) {
        // restore the widget to be focusable
        widget->setProperty("unfocus", false);
        SetWindowLong(hWnd, GWL_EXSTYLE, exs & ~WS_EX_NOACTIVATE & ~WS_EX_COMPOSITED);
    }
}
#endif

void WindowHelper::setTopmost(QWidget *widget, bool need_topmost)
{
    QWindow *window = widget->windowHandle();
    window->setFlag(Qt::WindowStaysOnTopHint, need_topmost);
    window->setProperty("topmost", need_topmost);
}


#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

#include <qglobal.h>

class QWidget;

namespace WindowHelper
{
#ifdef Q_OS_WIN
void setWindowUnfocusable(QWidget *widget, bool need_unfocus);
#endif

void setTopmost(QWidget *widget, bool need_topmost);
}

#endif // WINDOWHELPER_H

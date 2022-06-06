#ifndef UTIL_H
#define UTIL_H

#include <QtGlobal>

class QString;
class QObject;
class QWidget;

namespace Util
{
    void loadStyleSheet(const QString &path);
    void dumpStructure(const QObject *obj, int spaceCount = 0);

    #ifdef Q_OS_WIN
    void setWindowUnfocusable(QWidget *widget);
    #endif
}

#endif // UTIL_H

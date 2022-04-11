#ifndef PASTEUTIL_H
#define PASTEUTIL_H

#include <QApplication>
#include "Singleton.h"

class PasteUtil
{
    SINGLETON(PasteUtil)
public:
    void paste(const QString &str);
    void paste();

private:
    QClipboard *_clipBoard = qApp->clipboard();
};

#endif // PASTEUTIL_H

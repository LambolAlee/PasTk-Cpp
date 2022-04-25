#ifndef PASTEUTIL_H
#define PASTEUTIL_H

#include <QApplication>
#include "Singleton.h"

class PasteUtil : public QObject
{
    Q_OBJECT
    SINGLETON(PasteUtil)
public:
    void paste(const QString &str);
    void paste(bool directly = false);

private slots:
    void _paste() const;

private:
    QClipboard *_clipBoard = qApp->clipboard();
};

#endif // PASTEUTIL_H

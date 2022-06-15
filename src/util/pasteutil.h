#ifndef PASTEUTIL_H
#define PASTEUTIL_H

#include <QApplication>

#include "util/postoffice.h"


class PasteUtil : public QObject
{
    Q_OBJECT
    SINGLETON(PasteUtil)
public:
    void paste(const QString &str, bool directly);
    void quickPaste(const QString &str);

private slots:
    void _paste() const;

private:
    QClipboard *_clipBoard = qApp->clipboard();

    void paste(bool directly = false, bool needQuickPaste = false);
};

#endif // PASTEUTIL_H

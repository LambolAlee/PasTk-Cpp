#ifndef PASTEMANAGER_H
#define PASTEMANAGER_H

#include <QObject>


class PasteManager : public QObject
{
    Q_OBJECT
public:
    enum PasteMode {
        Merge,
        Continuous,
        Selection,
    };

    void startPaste(int mode, bool needReport);

signals:
    void pasteOver();
};

#endif // PASTEMANAGER_H

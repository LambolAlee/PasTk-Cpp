#ifndef PASTEUTIL_H
#define PASTEUTIL_H

#include <QObject>
#include "src/utils/Singleton.h"


class PasteUtil : public QObject
{
    Q_OBJECT
    SINGLETON(PasteUtil)

public:
    void paste([[maybe_unused]] QWidget *window);

private slots:
    void execute_paste();
};

#endif // PASTEUTIL_H

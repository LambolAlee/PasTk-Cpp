#ifndef PASTEUTIL_H
#define PASTEUTIL_H

#include <QObject>
#include "src/utils/Singleton.h"


class PasteUtil : public QObject
{
    Q_OBJECT
    SINGLETON(PasteUtil)

public:
    void paste(QWidget *window);
    void paste();
    void test();

private:
    void execute_paste();
};

#endif // PASTEUTIL_H

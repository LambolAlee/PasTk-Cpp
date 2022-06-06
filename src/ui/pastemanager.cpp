#include "pastemanager.h"
#include "continuouspastewindow.h"
#include "selectionpastewindow.h"
#include "mergewindow.h"

#include <QDebug>


void PasteManager::startPaste(int mode, bool needReport)
{
    switch (mode) {
    case Merge: {
        MergeWindow *w = new MergeWindow;
        w->show();
        break;
    }
    case Continuous: {
        ContinuousPasteWindow *w = new ContinuousPasteWindow;
        w->show();
        break;
    }
    case Selection: {
        SelectionPasteWindow *w = new SelectionPasteWindow;
        w->show();
        break;
    }
    }

    if (needReport)
        emit pasteOver();
}

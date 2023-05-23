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
        if (needReport) connect(w, &MergeWindow::reportQuit, this, &PasteManager::pasteOver);
        w->show();
        break;
    }
    case Continuous: {
        ContinuousPasteWindow *w = new ContinuousPasteWindow;
        if (needReport) connect(w, &ContinuousPasteWindow::reportQuit, this, &PasteManager::pasteOver);
        w->show();
        break;
    }
    case Selection: {
        SelectionPasteWindow *w = new SelectionPasteWindow;
        if (needReport) connect(w, &SelectionPasteWindow::reportQuit, this, &PasteManager::pasteOver);
        w->show();
        break;
    }
    }
}

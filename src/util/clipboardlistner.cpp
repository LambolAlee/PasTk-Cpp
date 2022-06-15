#include "clipboardlistner.h"
#include "datamanager/datamanager.h"

#include <QClipboard>


void ClipBoardListner::start()
{
    _inCopying = true;
    connect(_clipboard, &QClipboard::dataChanged, this, &ClipBoardListner::push);
}

void ClipBoardListner::stop()
{
    _inCopying = false;
    disconnect(_clipboard, &QClipboard::dataChanged, this, 0);
}

bool ClipBoardListner::isCopying()
{
    return _inCopying;
}

void ClipBoardListner::startQuickPaste()
{
    _clipboard->blockSignals(true);
}

void ClipBoardListner::endQuickPaste()
{
    _clipboard->blockSignals(false);
}

void ClipBoardListner::push()
{
    auto text = _clipboard->text();
    if (!text.isEmpty()) {
        DataManager::instance().insert(text);
        emit updateCount();
    }
}

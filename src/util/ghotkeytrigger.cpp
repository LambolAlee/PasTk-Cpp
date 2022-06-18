#include "ghotkeytrigger.h"
#include "config.h"
#include "postoffice.h"

#include <QApplication>


GHotkeyTrigger::GHotkeyTrigger()
{
    updateShortcuts();
    connectSignalsWithSlots();
}

GHotkeyTrigger::~GHotkeyTrigger()
{
    clear();
}

void GHotkeyTrigger::setHotkey(const QString &name, const QKeySequence &sequence, bool autoRegister)
{
    if (contains(name))
         value(name)->setShortcut(sequence, autoRegister);
    insert(name, new QHotkey(sequence, autoRegister, qApp));
}

void GHotkeyTrigger::updateShortcuts()
{
    Config config;

    setHotkey("copy", config.getCopyShortcut(), true);
    setHotkey("runPaste", config.getRunPasteShortcut(), true);
    setHotkey("paste", config.getPasteShortcut());
    setHotkey("skip", config.getSkipShortcut());
}

void GHotkeyTrigger::connectSignalsWithSlots()
{
    auto &poster = PostOffice::instance();
    poster.upload(this, "update_shortcuts", SIGNAL(updateShortcutsSig()), "updateShortcutsSig");
    poster.subscribe(this, "update_shortcuts", SLOT(updateShortcuts()));
}

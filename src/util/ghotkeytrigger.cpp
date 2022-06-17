#include "ghotkeytrigger.h"
#include "config.h"
#include "postoffice.h"


GHotkeyTrigger::GHotkeyTrigger()
{
    updateShortcuts();
    connectSignalsWithSlots();
}

GHotkeyTrigger::~GHotkeyTrigger()
{
    auto hotkeys = values();
    qDeleteAll(hotkeys);
    clear();
}

void GHotkeyTrigger::setHotkey(const QString &name, const QKeySequence &sequence)
{
    if (contains(name))
         delete take(name);
    insert(name, new QHotkey(sequence, true, this));
}

void GHotkeyTrigger::update(const QString &name, const QKeySequence &sequence)
{
    if (!contains(name)) return;
    value(name)->setShortcut(sequence, true);
}

void GHotkeyTrigger::updateShortcuts()
{
    Config config;

    setHotkey("copy", config.getCopyShortcut());
    setHotkey("runPaste", config.getRunPasteShortcut());
    setHotkey("paste", config.getPasteShortcut());
    setHotkey("skip", config.getSkipShortcut());
}

void GHotkeyTrigger::connectSignalsWithSlots()
{
    PostOffice::instance().upload(this, "update_shortcuts", SIGNAL(updateShortcutsSig()), "updateShortcutsSig");
    PostOffice::instance().subscribe(this, "update_shortcuts", SLOT(updateShortcuts()));
}

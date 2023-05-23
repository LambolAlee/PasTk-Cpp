#include "systray.h"

#include <QMenu>
#include <QApplication>
#include <QKeySequence>

#include "util/postoffice.h"
#include "util/ghotkeytrigger.h"
#include "home.h"


SysTray::SysTray(Home *home, QObject */*parent*/)
{
    _home = home;
    initUI();

    connectSignalsWithSlots();
}

SysTray::~SysTray()
{
    delete _menu;
}

void SysTray::showHome()
{
#ifdef Q_OS_MAC
    static bool firstShow = true;
    if (firstShow) {
        firstShow = false;
        _home->resize(0, 400);
    }
    _home->show();
#elif defined Q_OS_WIN
    PostOffice::instance().post("home_show");
#endif
}

void SysTray::activateHandler(ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick: {
        showHome();
        break;
    }
    default:
        break;
    }
}

void SysTray::initUI()
{
    _menu = new QMenu;
    auto actions = _home->bottomBarActions();
    _menu->addAction(actions.at(0));    // copy action
    _menu->addAction(actions.at(1));        // clear action

    // runPaste action, but it's treated as a menu in systray menu
    // so I new a new runPaste action to stand for the old runPaste action
    QAction *runPasteOld = actions.at(2);
    QAction *modes = _menu->addAction("Select Modes");
    modes->setMenu(runPasteOld->menu());
    QAction *runPaste = _menu->addAction("Paste");
    runPaste->setIcon(runPasteOld->icon());
    runPaste->setShortcut(runPasteOld->shortcut());
    connect(runPaste, &QAction::triggered, runPasteOld, &QAction::trigger);

    _menu->addSeparator();
    _menu->addAction("Show Home Window", this, &SysTray::showHome);
    _menu->addSeparator();
    _menu->addAction(_home->preferencesAction());
    _menu->addSeparator();
    _menu->addAction("Quit", qApp, &QApplication::quit);

    setContextMenu(_menu);
    setIcon(QIcon(":/logo/PasTk_logo_128.png"));
}

void SysTray::connectSignalsWithSlots()
{
    connect(this, &SysTray::activated, this, &SysTray::activateHandler);
    connect(GHotkeyTrigger::instance().value("show_home_window"), &QHotkey::activated, this, &SysTray::showHome);
}

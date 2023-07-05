#include "systray.h"

#include <QMenu>
#include <QApplication>
#include <QKeySequence>

//#include "util/postoffice.h"
//#include "util/ghotkeytrigger.h"
#include "src/ui/pastkwindow.h"


SysTray::SysTray(PasTkWindow *window, QObject */*parent*/)
{
    m_window = window;
    initUI();

    connectSignalsWithSlots();
}

SysTray::~SysTray()
{
    delete m_menu;
    m_window = nullptr;
}

void SysTray::showWindow()
{
    m_window->show();
    m_window->activateWindow();
    m_window->raise();
}

void SysTray::activateHandler(ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick: {
        showWindow();
        break;
    }
    default:
        break;
    }
}

void SysTray::initUI()
{
    m_menu = new QMenu;
    auto actions = m_window->bottomBarActions();
    m_menu->addAction(actions.at(0));    // switch action
    m_menu->addAction(actions.at(1));    // clear action
    m_menu->addAction(actions.at(2));    // paste action

    m_menu->addSeparator();
    m_menu->addAction("Show Home Window", this, &SysTray::showWindow);
    m_menu->addSeparator();
    m_menu->addAction(m_window->preferencesAction());
    m_menu->addSeparator();
    auto *tools = m_window->toolMenu();
    for (auto *action: tools->actions())
        m_menu->addAction(action);
    m_menu->addSeparator();
    auto *help = m_window->helpMenu();
    for (auto *action: help->actions())
        m_menu->addAction(action);
    m_menu->addSeparator();
    m_menu->addAction("Quit", qApp, &QApplication::quit);

    setContextMenu(m_menu);
    setIcon(QIcon(":/PasTk_logo_128.png"));
}

void SysTray::connectSignalsWithSlots()
{
    connect(this, &SysTray::activated, this, &SysTray::activateHandler);
//    connect(GHotkeyTrigger::instance().value("show_home_window"), &QHotkey::activated, this, &SysTray::showHome);
}

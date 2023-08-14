#include "systray.h"
#include "src/ui/pastkwindow.h"
#include <QMenu>
#include <QApplication>


SysTray::SysTray(PasTkWindow *window, QObject */*parent*/)
{
    initUI(window);

    connect(this, &SysTray::activated, this, [window](ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::DoubleClick: {
            window->linkTrayShowAction();
            break;
        }
        default:
            break;
        }
    });
}

SysTray::~SysTray()
{
    delete m_menu;
}

void SysTray::initUI(PasTkWindow *window)
{
    m_menu = new QMenu;
    auto actions = window->bottomBarActions();
    // switch action
    m_menu->addAction(actions.at(0));
    // clear action
    auto raw_clear_action = actions.at(1);
    auto clear_action = new QAction(raw_clear_action->icon(), "Clear All Items");
    connect(clear_action, &QAction::triggered, window, &PasTkWindow::linkTrayClearAllAction);
    connect(raw_clear_action, &QAction::enabledChanged, clear_action, &QAction::setEnabled);
    m_menu->addAction(clear_action);

    // paste action
    auto raw_paste_action = actions.at(2);
    auto paste_selector = new QAction("Select Paste Mode");
    paste_selector->setMenu(raw_paste_action->menu());
    auto paste_operator = new QAction(raw_paste_action->icon(), raw_paste_action->text());
    connect(paste_operator, &QAction::triggered, window, &PasTkWindow::linkTrayPasteAction);
    connect(raw_paste_action, &QAction::enabledChanged, paste_operator, &QAction::setEnabled);
    m_menu->addActions({paste_selector, paste_operator});

    m_menu->addSeparator();
    m_menu->addAction("Show Home Window", window, &PasTkWindow::linkTrayShowAction);
    m_menu->addSeparator();
    m_menu->addAction(window->preferencesAction());
    m_menu->addSeparator();
    auto *tools = window->toolMenu();
    for (auto *action: tools->actions())
        m_menu->addAction(action);
    m_menu->addSeparator();
    auto *help = window->helpMenu();
    for (auto *action: help->actions())
        m_menu->addAction(action);
    m_menu->addSeparator();
    m_menu->addAction("Quit", qApp, &QApplication::quit);

    setContextMenu(m_menu);
    setIcon(QIcon(":/PasTk_logo_128.png"));
}

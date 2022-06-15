#include "systray.h"

#include <QMenu>
#include <QApplication>
#include <QKeySequence>

#include "util/postoffice.h"
#include "util/config.h"


SysTray::SysTray(Home *home, QObject */*parent*/)
{
    _home = home;
    initUI();
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
    PostOffice::instance().publish("home_show");
#endif
}

void SysTray::initUI()
{
    _menu = new QMenu;
    _record = _menu->addAction("Record");
    _paste = _menu->addAction("Paste", this, []{qDebug() << "hello world";});
    _menu->addAction("Reset");
    _menu->addSeparator();
    _menu->addAction("Show Home Window", this, &SysTray::showHome);
    _menu->addSeparator();
    _menu->addAction("Preferences");
    _menu->addSeparator();
    _menu->addAction("Quit", qApp, &QApplication::quit);

    setContextMenu(_menu);
    setIcon(QIcon(":/logo/PasTk_logo_128.png"));
}

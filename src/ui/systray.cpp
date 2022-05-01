#include "systray.h"

#include <QMenu>
#include <QApplication>


SysTray::SysTray(QWidget *home, QObject */*parent*/)
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
#endif
    _home->show();
}

void SysTray::initUI()
{
    _menu = new QMenu;
    _menu->addAction("Record");
    _menu->addAction("Paste", this, []{qDebug() << "hello world";});
    _menu->addAction("Reset");
    _menu->addSeparator();
    _menu->addAction("Show Home Window", this, &SysTray::showHome);
    _menu->addSeparator();
    _menu->addAction("Preferences");
    _menu->addSeparator();
    _menu->addAction("Quit", qApp, &QApplication::quit);

    setContextMenu(_menu);
    setIcon(QIcon(":/icons/clipboard.svg"));
}

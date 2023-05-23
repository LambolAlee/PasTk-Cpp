#include "ui/home.h"
#include "SingleApplication"
#include "ui/systray.h"
#include "util/util.h"
#include "util/config.h"
#include <QDir>
#include <QApplication>

#ifdef Q_OS_WIN
#include "ui/framelesswindow.h"
#endif

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);
    a.setOrganizationDomain("lambol.pastk-cpp.org");
    a.setOrganizationName("Lambol.Michael.Alee");
    a.setApplicationName("PasTk-Cpp");
    a.setQuitOnLastWindowClosed(false);

    Home w;
    Util::loadStyleSheet(":/style/basic_style.qss");
    SysTray tray(&w);
    tray.show();

#ifdef Q_OS_WIN
    Util::loadStyleSheet(":/style/font-win.qss");
    TitleBar titleBar;
    CFramelessWindow *frameless = new CFramelessWindow; // ??? if not newing an object, it will crash while quitting
    frameless->makeFrameless(&w, &titleBar, titleBar.titleWidget());
    if (Config().getWindowVisible())
        frameless->show();
    else
        tray.showMessage("PasTk - Cpp", "PasTk is waiting for commands");
#elif defined Q_OS_MAC
    Util::loadStyleSheet(":/style/font-mac.qss");
    if (Config().getWindowVisible())
        w.show();
    else
        tray.showMessage("PasTk - Cpp", "PasTk is waiting for commands");
#endif
    return a.exec();
}

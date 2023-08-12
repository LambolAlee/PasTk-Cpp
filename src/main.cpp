#include "ui/pastkwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include "src/ui/systray.h"
#include "src/utils/util.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("lambol.pastk-cpp.org");
    a.setOrganizationName("Lambol.Michael.Alee");
    a.setApplicationName("PasTk-Cpp");
    a.setQuitOnLastWindowClosed(false);

    Util::loadStyleSheet(":/styles/basic_style.qss");

#ifdef Q_OS_MAC
//    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyle(QStyleFactory::create("Windows"));
    Util::loadStyleSheet(":/styles/font-mac.qss");
#elif defined Q_OS_WIN
    Util::loadStyleSheet(":/styles/font-win.qss");
#endif

    PasTkWindow w;
    SysTray tray(&w);
    tray.show();
    w.show();
    return a.exec();
}

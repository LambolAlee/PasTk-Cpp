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

#ifdef Q_OS_MAC
//    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyle(QStyleFactory::create("Windows"));
#endif

    PasTkWindow w;
    Util::loadStyleSheet(":/styles/basic_style.qss");
    SysTray tray(&w);
    tray.show();
    w.show();
    return a.exec();
}

#include "ui/pastkwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include "src/ui/systray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef Q_OS_MAC
    a.setStyle(QStyleFactory::create("Fusion"));
#endif

    PasTkWindow w;
    SysTray tray(&w);
    tray.show();
    return a.exec();
}

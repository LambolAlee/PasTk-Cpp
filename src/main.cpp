#include "ui/pastkwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef Q_OS_MAC
    a.setStyle(QStyleFactory::create("Fusion"));
#endif

    PasTkWindow w;
    w.show();
    return a.exec();
}

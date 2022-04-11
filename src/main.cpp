#include "ui/home.h"
//#include "QHotkey"
#include "SingleApplication"
#include "ui/framelesswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);

    Home w;
    TitleBar titleBar;
    CFramelessWindow *frameless = new CFramelessWindow; // ??? if not newing an object, it will crash while quitting
    frameless->makeFrameless(&w, &titleBar, titleBar.titleWidget());

    frameless->show();
    return a.exec();
}

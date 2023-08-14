#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QSystemTrayIcon>


class QAction;
class PasTkWindow;

class SysTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    SysTray(PasTkWindow *window, QObject *parent = nullptr);
    ~SysTray();

private:
    QMenu *m_menu;

    void initUI(PasTkWindow *window);
};

#endif // SYSTRAY_H

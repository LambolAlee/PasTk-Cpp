#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QSystemTrayIcon>


class QAction;
class Home;

class SysTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    SysTray(Home *home, QObject *parent = nullptr);
    ~SysTray();

private slots:
    void showHome();

private:
    Home *_home;
    QMenu *_menu;
    QAction *_record;
    QAction *_paste;

    void initUI();
};

#endif // SYSTRAY_H

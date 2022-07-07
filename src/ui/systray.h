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
    void activateHandler(QSystemTrayIcon::ActivationReason reason);

private:
    Home *_home;
    QMenu *_menu;
    QAction *_record;
    QAction *_paste;

    void initUI();
    void connectSignalsWithSlots();
};

#endif // SYSTRAY_H

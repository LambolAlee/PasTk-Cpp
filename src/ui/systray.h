#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QSystemTrayIcon>


class SysTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    SysTray(QWidget *home, QObject *parent = nullptr);
    ~SysTray();

private slots:
    void showHome();

private:
    QWidget *_home;
    QMenu *_menu;

    void initUI();
};

#endif // SYSTRAY_H

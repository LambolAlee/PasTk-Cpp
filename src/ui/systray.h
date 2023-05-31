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

private slots:
    void showWindow();
    void activateHandler(QSystemTrayIcon::ActivationReason reason);

private:
    PasTkWindow *m_window;
    QMenu *m_menu;
//    QAction *m_record;
//    QAction *m_paste;

    void initUI();
    void connectSignalsWithSlots();
};

#endif // SYSTRAY_H

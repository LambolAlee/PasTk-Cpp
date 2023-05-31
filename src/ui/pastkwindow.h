#ifndef PASTKWINDOW_H
#define PASTKWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class PasTkWindow; }
QT_END_NAMESPACE

class BottomBar;

class PasTkWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(bool topmost READ topmost WRITE setTopmost NOTIFY topmostChanged)
    Q_PROPERTY(bool unfocus READ unfocus WRITE setUnfocus)

public:
    PasTkWindow(QWidget *parent = nullptr);
    ~PasTkWindow();

    const QList<QAction *> bottomBarActions();
    QAction *preferencesAction();

signals:
    void topmostChanged(bool current);

public:
    bool topmost() const;
    void setTopmost(bool value);

    bool unfocus() const;
    void setUnfocus(bool value);

private slots:
    void showDetailContent();

private:
    void connectSignalsWithSlots();
    void buildBottomBar();

private:
    Ui::PasTkWindow *ui;
    BottomBar *m_bottombar;
    QActionGroup *m_mode_actions;

    QIcon m_pin;
    QIcon m_unpin;

    bool m_topmost;
    bool m_unfocus;
    void initModeActions();
};
#endif // PASTKWINDOW_H

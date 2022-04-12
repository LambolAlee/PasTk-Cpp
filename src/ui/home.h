#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

class BottomBar;

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void toggleMenubar();
    void triggerAboutQtAction();

private:
    Ui::Home *ui;
    BottomBar *_bottomBar;
    void connectSignalsWithSlots();
};
#endif // HOME_H

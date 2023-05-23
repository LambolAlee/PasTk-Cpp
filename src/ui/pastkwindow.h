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

public:
    PasTkWindow(QWidget *parent = nullptr);
    ~PasTkWindow();

private slots:
    void showDetailContent();

private:
    void connectSignalsWithSlots();
    void buildBottomBar();

private:
    Ui::PasTkWindow *ui;
    BottomBar *m_bottombar;

};
#endif // PASTKWINDOW_H

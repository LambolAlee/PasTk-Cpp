#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

namespace Ui {
class BottomBar;
}

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();

    void triggerSwitchAction();

signals:
    void clearAllItems();
    void startPaste();
    void switchState(bool state);

    void noData();

public slots:
    void updateCounter();

private slots:
    void toggleSwitch(bool state);

private:
    Ui::BottomBar *ui;

    void connectSignalsWithSlots();
};

#endif // BOTTOMBAR_H

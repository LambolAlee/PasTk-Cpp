#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

namespace Ui {
class BottomBar;
}

class QActionGroup;

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();

    void triggerSwitchAction();
    void setModeActions(QActionGroup *modeActions);
    void setDeleteBtnDisabled(bool disable);

signals:
    void clearItems();
    void startPaste();
    void switchState(bool state);

    void noData();

public slots:
    void updateCounter();

private slots:
    void toggleSwitch(bool state);

private:
    Ui::BottomBar *ui;
    QActionGroup *_modeActions;

    void connectSignalsWithSlots();
};

#endif // BOTTOMBAR_H

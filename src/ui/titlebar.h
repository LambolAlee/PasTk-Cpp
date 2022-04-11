#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

#include "util/cframelessbridge.h"

class QLabel;

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    QLabel *titleWidget();

private slots:
    void closeButtonClicked();
    void minimizeButtonClicked();
    void topmostButtonToggled();

private:
    Ui::TitleBar *ui;
    CFramelessBridge &_bridge = CFramelessBridge::instance();

    void connectSignalsWithSlots();
};

#endif // TITLEBAR_H

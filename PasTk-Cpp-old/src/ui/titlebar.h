#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

#include "util/postoffice.h"


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
    PostOffice &_poster = PostOffice::instance();

    void connectSignalsWithSlots();

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
};

#endif // TITLEBAR_H

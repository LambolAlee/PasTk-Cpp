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

    void setModeActions(QActionGroup *group);
    const QList<QAction *> actions();

private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_H

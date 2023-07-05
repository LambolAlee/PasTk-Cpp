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

    void switchCopy(bool on);
    void setClearActionDisabled(bool disabled);
    void setBottomBarEnabled(bool enabled);

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void switchActionToggled(bool state);
    void clearSelectedItems();
    void clearAllTriggered();
    void startPaste();

public slots:
    void updateCount(int count);

private slots:
    void on_BottomBar_clearAllTriggered();

private:
    Ui::BottomBar *ui;

    QIcon m_start;
    QIcon m_pause;

};

#endif // BOTTOMBAR_H

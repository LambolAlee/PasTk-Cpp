#ifndef CONTINUOUSPASTEWIDGET_H
#define CONTINUOUSPASTEWIDGET_H

#include <QWidget>

namespace Ui {
class ContinuousPasteWidget;
}

class ContinuousPasteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContinuousPasteWidget(QWidget *parent = nullptr);
    ~ContinuousPasteWidget();

signals:
    void backToHome();

private:
    void connectSignalsWithSlots();

private:
    Ui::ContinuousPasteWidget *ui;
};

#endif // CONTINUOUSPASTEWIDGET_H

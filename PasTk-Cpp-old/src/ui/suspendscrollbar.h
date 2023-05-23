#ifndef SUSPENDSCROLLBAR_H
#define SUSPENDSCROLLBAR_H

#include <QScrollBar>

class SuspendScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    SuspendScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);

public slots:
    void handleRangeChanged(int min, int max);
    void handleValueChange(int value);
};

#endif // SUSPENDSCROLLBAR_H

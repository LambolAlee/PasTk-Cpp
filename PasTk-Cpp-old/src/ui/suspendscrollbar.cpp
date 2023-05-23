#include "suspendscrollbar.h"


SuspendScrollBar::SuspendScrollBar(Qt::Orientation orientation, QWidget *parent)
    : QScrollBar(parent)
{
    setOrientation(orientation);
    setRange(0,0);
    hide();
}

void SuspendScrollBar::handleRangeChanged(int min, int max)
{
    setMinimum(min);
    setRange(0 , max);
    setPageStep(0.75 * (this->height() + max));
    if(max <= 0)
        hide();
}

void SuspendScrollBar::handleValueChange(int value)
{
    setValue(value);
}

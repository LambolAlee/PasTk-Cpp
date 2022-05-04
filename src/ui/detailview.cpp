#include "detailview.h"
#include "suspendscrollbar.h"


DetailView::DetailView(QWidget *parent)
    : QListView(parent)
    , _scrollBar(new SuspendScrollBar(Qt::Vertical, this))
{
    setMouseTracking(true);
    setAlternatingRowColors(true);
    setSpacing(5);
    setAutoScroll(false);
    //setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //verticalScrollBar()->setSingleStep(15);
    setEditTriggers(QListView::NoEditTriggers);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connectSignalsWithSlots();
}

void DetailView::enterEvent(QEnterEvent *event)
{
    if (_scrollBar->maximum() > 0)
        _scrollBar->show();
    return QListView::enterEvent(event);
}

void DetailView::leaveEvent(QEvent *event)
{
    _scrollBar->hide();
    return QListView::leaveEvent(event);
}

void DetailView::resizeEvent(QResizeEvent *event)
{
    int iX = width() - 8;
    _scrollBar->setGeometry(iX,1,8,this->height()-2);
    return QListView::resizeEvent(event);
}

QModelIndexList DetailView::selectedIndexes() const
{
    return QListView::selectedIndexes();
}

void DetailView::syncWithSuspendScroll(int value)
{
    verticalScrollBar()->setValue(value);
}

void DetailView::connectSignalsWithSlots()
{
    connect(verticalScrollBar(), &QScrollBar::valueChanged, _scrollBar, &SuspendScrollBar::handleValueChange);
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, _scrollBar, &SuspendScrollBar::handleRangeChanged);
    connect(_scrollBar, &SuspendScrollBar::valueChanged, this, &DetailView::syncWithSuspendScroll);
}

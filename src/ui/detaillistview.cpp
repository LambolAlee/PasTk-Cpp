#include "detaillistview.h"
#include "itemfloatbuttons.h"

#include <QMouseEvent>


DetailListView::DetailListView(QWidget *parent)
    : QListView(parent)
{
    setMouseTracking(true);
    setAlternatingRowColors(true);
    setSpacing(5);
    setEditTriggers(QListView::NoEditTriggers);
    connectSignalsWithSlots();
}

void DetailListView::paintEvent(QPaintEvent *event)
{
//    auto index = indexAt(mapFromGlobal(QCursor::pos()));
//    if (_previousIdx.isValid())
//        setIndexWidget(_previousIdx, nullptr);
//    if (auto *editor = indexWidget(index); index.isValid() && !editor) {
//        setIndexWidget(index, new ItemFloatButtons);
//        _previousIdx = index;
//    }
    return QListView::paintEvent(event);
}

void DetailListView::connectSignalsWithSlots()
{

}

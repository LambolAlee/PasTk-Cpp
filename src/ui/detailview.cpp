#include "detailview.h"
#include "suspendscrollbar.h"

#include <QMenu>
#include <QContextMenuEvent>


DetailView::DetailView(QWidget *parent)
    : QListView(parent)
    , m_scrollBar(new SuspendScrollBar(Qt::Vertical, this))
    , m_menu(new QMenu(this))
{
    setMouseTracking(true);
    setAutoScroll(false);
    setAlternatingRowColors(true);
    setEditTriggers(QListView::NoEditTriggers);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    initContextMenu();
    connectSignalsWithSlots();
}

void DetailView::enterEvent(QEnterEvent *event)
{
    if (m_scrollBar->maximum() > 0)
        m_scrollBar->show();
    return QListView::enterEvent(event);
}

void DetailView::leaveEvent(QEvent *event)
{
    m_scrollBar->hide();
    return QListView::leaveEvent(event);
}

void DetailView::resizeEvent(QResizeEvent *event)
{
    int iX = width() - 8;
    m_scrollBar->setGeometry(iX,1,8,this->height()-2);
    return QListView::resizeEvent(event);
}

void DetailView::contextMenuEvent(QContextMenuEvent *event)
{
    bool pos_on_item = indexAt(event->pos()).isValid();
    m_delete->setVisible(pos_on_item);
    m_edit->setVisible(pos_on_item);
    m_add->setVisible(pos_on_item);
    m_add_last->setVisible(!pos_on_item);
    m_quick_paste->setVisible(pos_on_item);

    m_menu->exec(event->globalPos());
    event->accept();
}

QModelIndexList DetailView::selectedIndexes() const
{
    return QListView::selectedIndexes();
}

void DetailView::syncWithSuspendScroll(int value)
{
    verticalScrollBar()->setValue(value);
}

void DetailView::initContextMenu()
{
    m_delete = new QAction("Delete", m_menu);
    m_add = new QAction("Add", m_menu);
    m_edit = new QAction("Edit", m_menu);
    m_add_last = new QAction("Add", m_menu);
    m_quick_paste = new QAction("Quick Paste", m_menu);

    m_menu->addActions({m_edit, m_add, m_delete, m_add_last, m_quick_paste});
}

void DetailView::connectSignalsWithSlots()
{
    connect(verticalScrollBar(), &QScrollBar::valueChanged, m_scrollBar, &SuspendScrollBar::handleValueChange);
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, m_scrollBar, &SuspendScrollBar::handleRangeChanged);
    connect(m_scrollBar, &SuspendScrollBar::valueChanged, this, &DetailView::syncWithSuspendScroll);
    connect(m_delete, &QAction::triggered, this, &DetailView::deleteItem);
    connect(m_add, &QAction::triggered, this, &DetailView::newItemAddManuallyBefore);
    connect(m_add_last, &QAction::triggered, this, &DetailView::newItemAddManuallyAfter);
    connect(m_edit, &QAction::triggered, this, &DetailView::editItem);
    connect(m_quick_paste, &QAction::triggered, this, &DetailView::quickPaste);
    connect(this, &DetailView::doubleClicked, this, &DetailView::quickPaste);
}

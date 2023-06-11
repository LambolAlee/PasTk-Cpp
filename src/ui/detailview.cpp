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
    if (indexAt(event->pos()).isValid()) {
        m_delete->setVisible(true);
        m_edit->setVisible(true);
        m_add->setVisible(true);
        m_add_last->setVisible(false);
    } else {
        m_delete->setVisible(false);
        m_edit->setVisible(false);
        m_add->setVisible(false);
        m_add_last->setVisible(true);
    }
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
    m_delete = new QAction(m_menu);
    m_delete->setText("Delete");

    m_add = new QAction(m_menu);
    m_add->setText("Add");

    m_edit = new QAction(m_menu);
    m_edit->setText("Edit");

    m_add_last = new QAction(m_menu);
    m_add_last->setText("Add");

    m_menu->addActions({m_edit, m_add, m_delete, m_add_last});
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
}

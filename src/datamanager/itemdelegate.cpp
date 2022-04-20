#include "itemdelegate.h"

#include <QPainter>
#include <QApplication>


ItemDelegate::ItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , _editTB(new QToolButton)
    , _deleteTB(new QToolButton)
    , _quickPasteTB(new QToolButton)
{}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(0, 36);
}

void ItemDelegate::paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const
{
    painter->save();
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(QBrush(QColor(253, 246, 227, 200)));
    } else if (option.state & QStyle::State_MouseOver) {
        painter->setBrush(QBrush(QColor(253, 246, 227, 100)));
    }
    painter->drawRoundedRect(option.rect, 5, 5);
    painter->restore();
}

void ItemDelegate::drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &/*option*/) const
{
    painter->save();

    painter->restore();
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) return;
    painter->save();

    paintBackGround(painter, option);
    qDebug() << option.state;
    if (option.state.testFlag(QStyle::State_Enabled)) {
        QPoint topLeft = option.rect.topLeft();
        QPoint bottomLeft = option.rect.bottomLeft();

        QPoint picP = QPoint(topLeft.x()+5, topLeft.y()+7);
        painter->drawPixmap(picP, QPixmap(":/icons/text.svg"));

        QFont font;
        font.setPointSize(10);
        painter->setFont(font);
        QPoint textP = QPoint(bottomLeft.x()+33, bottomLeft.y()-18+painter->fontMetrics().height()/2);
        painter->drawText(textP, index.data().toString());
    }

    painter->restore();
}

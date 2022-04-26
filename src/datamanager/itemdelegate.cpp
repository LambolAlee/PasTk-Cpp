#include "itemdelegate.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QStyleOptionToolButton>


ItemDelegate::ItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , _state(Normal)
    , _lastUpdatedTBIndex(-1)
    , _editTB(new QToolButton)
    , _deleteTB(new QToolButton)
    , _quickPasteTB(new QToolButton)
{
    auto delegateTB = "DelegateTB";
    _editTB->setProperty("class", delegateTB); _editTB->setObjectName("editTB");
    _deleteTB->setProperty("class", delegateTB); _deleteTB->setObjectName("deleteTB");
    _quickPasteTB->setProperty("class", delegateTB); _quickPasteTB->setObjectName("pasteTB");

    _iconList << "delete_one" << "execute_normal" << "edit";
    _btnList << _deleteTB << _quickPasteTB << _editTB;

    _signalMap.insert(_editTB, &ItemDelegate::doEdit);
    _signalMap.insert(_deleteTB, &ItemDelegate::doDelete);
    _signalMap.insert(_quickPasteTB, &ItemDelegate::doPaste);

    connectSignalsWithSlots();
}

ItemDelegate::~ItemDelegate()
{
    qDeleteAll(_btnList);
}

void ItemDelegate::connectSignalsWithSlots()
{
    connect(this, &ItemDelegate::doDelete, &ItemDelegate::deleteOne);
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(0, HEIGHT);
}

void ItemDelegate::paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const
{
    painter->save();
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(QBrush(bgColorSelected));
    } else if (option.state & QStyle::State_MouseOver) {
        painter->setBrush(QBrush(bgColorHovered));
    }
    painter->drawRoundedRect(option.rect, radius, radius);
    painter->restore();
}

QPoint ItemDelegate::getItemBtnTopLeft(const QStyleOptionViewItem &option) const
{
    auto topRight = option.rect.topRight();
    QPoint btnTopLeft = QPoint(topRight.x()-marginToBorder-iconRectBorder,
                                        topRight.y()+HEIGHT/2-iconRectBorder/2);
    return btnTopLeft;
}

void ItemDelegate::drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &option) const
{
    auto btnTopLeft = getItemBtnTopLeft(option);

    painter->save();
    for (int i = 0; i < _btnList.count(); ++i) {
        QStyleOptionToolButton opt;

        opt.rect = QRect(btnTopLeft, iconRectSize);
        btnTopLeft.rx() -= distBetweenBtns;

        opt.icon = QIcon(QString(":/icons/%1.svg").arg(_iconList.at(i)));
        opt.iconSize = iconSizeQ;
        opt.state |= QStyle::State_Enabled | QStyle::State_AutoRaise;

        if (opt.rect.contains(_mousePos)) {
            switch (_state) {
            case Press:
                opt.state |= QStyle::State_Sunken;
                break;
            case Hover:
                opt.state |= QStyle::State_MouseOver;
                break;
            default:
                break;
            }
        }

        _btnList.at(i)->style()->drawComplexControl(QStyle::CC_ToolButton, &opt, painter, _btnList.at(i));
    }
    painter->restore();
}

const QString ItemDelegate::formatText(const QModelIndex &index) const
{
    return index.data().toString();
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) return;
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    paintBackGround(painter, option);

    if (option.state & QStyle::State_Enabled) {
        if (option.state & QStyle::State_MouseOver)
            drawEditorButtons(painter, option);

        QPoint topLeft = option.rect.topLeft();
        QPoint bottomLeft = option.rect.bottomLeft();

        QPoint picP = QPoint(topLeft.x()+radius, topLeft.y()+radius+2);
        painter->drawPixmap(picP, QPixmap(":/icons/text.svg"));

        QFont font;
        font.setPointSize(10);
        painter->setFont(font);
        QPoint textP = QPoint(bottomLeft.x()+33, bottomLeft.y()-18+painter->fontMetrics().height()/2);
        painter->drawText(textP, formatText(index));
    }

    painter->restore();
}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    bool repaint = false;

    if (!event->isSinglePointEvent())
        return repaint;

    QMouseEvent *e = static_cast<QMouseEvent *>(event);
    _mousePos = e->pos();

    auto btnTopLeft = getItemBtnTopLeft(option);
    QRect rect;
    for (int i = 0; i < _btnList.count(); ++i) {
        rect = QRect(btnTopLeft, iconRectSize);
        btnTopLeft.rx() -= distBetweenBtns;
        if (!rect.contains(_mousePos)) {
            continue;
        } else {
            _lastUpdatedTBIndex = i;
            repaint = true;
        }

        switch (event->type()) {
        case QEvent::MouseMove:
            _state = Hover;
            break;
        case QEvent::MouseButtonPress:
            _state = Press;
            break;
        case QEvent::MouseButtonRelease: {
//            qDebug() << "emit!";
            _state = Hover;
            emit (this->*_signalMap.value(_btnList.at(i)))(model, index);
            break;
        }
        default:
            _state = Normal;
            break;
        }
    }

    if (!repaint && _lastUpdatedTBIndex != -1) {
        repaint = true;
        _state = Normal;
        _lastUpdatedTBIndex = -1;
    }
    return repaint;
}

void ItemDelegate::deleteOne(QAbstractItemModel *model, const QModelIndex &index)
{
    QStandardItemModel *m = static_cast<QStandardItemModel *>(model);
    m->removeRow(index.row());
}

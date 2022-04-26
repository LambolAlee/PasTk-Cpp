#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>
#include <QToolButton>


class QToolButton;
class ItemDelegate;
class QStandardItemModel;

using signalFunc = void(ItemDelegate::*)(QAbstractItemModel *model, const QModelIndex &index);

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QObject *parent = nullptr);
    ~ItemDelegate();

signals:
    void doPaste(QAbstractItemModel *model, const QModelIndex &index);
    void doEdit(QAbstractItemModel *model, const QModelIndex &index);
    void doDelete(QAbstractItemModel *model, const QModelIndex &index);

// QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private slots:
    void deleteOne(QAbstractItemModel *model, const QModelIndex &index);

private:
    enum ButtonState {
        Normal,
        Hover,
        Press,
    };

    QHash<QToolButton *, signalFunc> _signalMap;

    QPoint getItemBtnTopLeft(const QStyleOptionViewItem &option) const;

    void paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &option) const;

    const QString formatText(const QModelIndex &index) const;

    void connectSignalsWithSlots();

private:
    // painter const value
    static constexpr int HEIGHT = 36;
    static constexpr int radius = 5;
    static constexpr int marginToBorder = 12;
    static constexpr int iconSize = 20;
    static constexpr int iconRectBorder = iconSize + 6;
    static constexpr QSize iconSizeQ = QSize(iconSize, iconSize);
    static constexpr QSize iconRectSize = QSize(iconRectBorder, iconRectBorder);
    static constexpr int marginBetweenBtns = 8;
    static constexpr int distBetweenBtns = marginBetweenBtns + iconSize;
    static constexpr QColor bgColorHovered = QColor(253, 246, 227, 130);
    static constexpr QColor bgColorSelected = QColor(253, 246, 227, 255);

    QList<QToolButton *> _btnList;
    QList<QString> _iconList;
    QPoint _mousePos;
    ButtonState _state;
    int _lastUpdatedTBIndex;

    QToolButton *_editTB;
    QToolButton *_deleteTB;
    QToolButton *_quickPasteTB;
};

#endif // ITEMDELEGATE_H

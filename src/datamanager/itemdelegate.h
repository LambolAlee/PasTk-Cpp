#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>
#include <QToolButton>


class QTimer;
class QToolButton;
class ItemDelegate;
class QStandardItemModel;

using signalFunc = void(ItemDelegate::*)(const QModelIndex &index, QAbstractItemModel *model);

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QObject *parent = nullptr, bool viewOnly = false);
    ~ItemDelegate();

signals:
    void doPaste(const QModelIndex &index, QAbstractItemModel *model);
    void doEdit(const QModelIndex &index, QAbstractItemModel *model);
    void doDelete(const QModelIndex &index, QAbstractItemModel *model);

// QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;

public:
    void setViewOnly(bool state);
    bool isViewOnlyState() const;

private:
    enum ButtonState {
        Normal,
        Hover,
        Press,
    };

    QHash<QToolButton *, signalFunc> _signalMap;

    QPoint getItemBtnTopLeft(const QStyleOptionViewItem &option) const;
    QPoint getTextTopLeft(QPainter *painter, const QStyleOptionViewItem &option) const;
    QRect getBtnMaskRect(const QStyleOptionViewItem &option) const;

    void setBgColor(QPainter *painter, const QStyleOptionViewItem &option) const;
    void paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawBasicItemView(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    const QString formatText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

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
    static constexpr QColor bgColorHovered = QColor(254, 250, 241);
    static constexpr QColor bgColorSelected = QColor(253, 246, 227);

    QList<QToolButton *> _btnList;
    QList<QString> _iconList;
    QPoint _mousePos;
    ButtonState _state;
    int _lastUpdatedTBIndex;
    bool _viewOnlyState;
    ButtonState _btnLikeState;    // make each list item behave like a button

    QToolButton *_editTB;
    QToolButton *_deleteTB;
    QToolButton *_quickPasteTB;   
};

#endif // ITEMDELEGATE_H

#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>
#include <QToolButton>


class QToolButton;

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QObject *parent = nullptr);
    ~ItemDelegate();

// QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    enum ButtonState {
        Normal,
        Hover,
        Press,
    };

    QPoint getItemBtnTopLeft(const QStyleOptionViewItem &option) const;

    void paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &option) const;

    const QString formatText(const QModelIndex &index) const;

private:
    static constexpr int HEIGHT = 36;
    static constexpr int radius = 5;
    static constexpr int marginToBorder = 12;
    static constexpr int iconSize = 22;
    static constexpr QSize iconSizeQ = QSize(iconSize, iconSize);
    static constexpr int marginBetweenBtns = 8;
    static constexpr int distBetweenBtns = marginBetweenBtns + iconSize;

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

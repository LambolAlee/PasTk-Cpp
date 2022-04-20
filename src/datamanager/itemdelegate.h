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

// QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void paintBackGround(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawEditorButtons(QPainter *painter, const QStyleOptionViewItem &option) const;

private:
    QScopedPointer<QToolButton> _editTB;
    QScopedPointer<QToolButton> _deleteTB;
    QScopedPointer<QToolButton> _quickPasteTB;
};

#endif // ITEMDELEGATE_H

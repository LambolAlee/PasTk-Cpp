
#ifndef TEMPLATELISTDELEGATE_H
#define TEMPLATELISTDELEGATE_H

#include <QStyledItemDelegate>


class TemplateListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TEMPLATELISTDELEGATE_H

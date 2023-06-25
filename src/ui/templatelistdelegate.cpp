
#include "templatelistdelegate.h"


void TemplateListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem o(option);
    bool favor = index.data(Qt::UserRole).toBool();
    o.font.setBold(favor);
    return QStyledItemDelegate::paint(painter, o, index);
}

QWidget *TemplateListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void TemplateListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QStyledItemDelegate::setEditorData(editor, index);
}

void TemplateListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QStyledItemDelegate::setModelData(editor, model, index);
}

void TemplateListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

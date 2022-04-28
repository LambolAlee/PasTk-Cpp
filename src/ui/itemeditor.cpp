#include "itemeditor.h"

#include <QModelIndex>
#include <QStyleOptionViewItem>


ItemEditor::ItemEditor(QWidget *parent)
    : QTextEdit(parent)
{

}

void ItemEditor::initUI(const QStyleOptionViewItem &option)
{
    setGeometry(option.rect);
}

void ItemEditor::setEditorData(const QModelIndex &index)
{
    setText(index.data().toString());
}

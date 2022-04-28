#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QTextEdit>


class QStyleOptionViewItem;

class ItemEditor : public QTextEdit
{
    Q_OBJECT
public:
    ItemEditor(QWidget *parent = nullptr);

    void initUI(const QStyleOptionViewItem &option);
    void setEditorData(const QModelIndex &index);
};

#endif // ITEMEDITOR_H

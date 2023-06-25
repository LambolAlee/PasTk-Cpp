#ifndef TAGSDRAWERCONTENT_H
#define TAGSDRAWERCONTENT_H

#include <QWidget>

namespace Ui {
class TagsDrawerContent;
}

class QListWidgetItem;

class TagsDrawerContent : public QWidget
{
    Q_OBJECT

public:
    explicit TagsDrawerContent(QWidget *parent = nullptr);
    ~TagsDrawerContent();

signals:
    void tagToBePasted(const QString &tag);

private slots:
    void showDoc(QListWidgetItem *item);

private:
    Ui::TagsDrawerContent *ui;
};

#endif // TAGSDRAWERCONTENT_H

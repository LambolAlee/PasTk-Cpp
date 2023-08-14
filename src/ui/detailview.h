#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include <QListView>


class SuspendScrollBar;

class DetailView : public QListView
{
    Q_OBJECT
public:
    DetailView(QWidget *parent = nullptr);

    QModelIndexList selectedIndexes() const override;

signals:
    void newItemAddManuallyBefore();
    void newItemAddManuallyAfter();
    void deleteItem();
    void editItem();
    void quickPaste();

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void syncWithSuspendScroll(int value);

private:
    void initContextMenu();

private:
    SuspendScrollBar *m_scrollBar;
    QMenu *m_menu;
    QAction *m_delete;
    QAction *m_add;
    QAction *m_edit;
    QAction *m_add_last;
    QAction *m_quick_paste;

    void connectSignalsWithSlots();
};

#endif // DETAILVIEW_H

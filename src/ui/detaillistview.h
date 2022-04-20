#ifndef DETAILLISTVIEW_H
#define DETAILLISTVIEW_H

#include <QListView>

class DetailListView : public QListView
{
    Q_OBJECT
public:
    DetailListView(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QModelIndex _previousIdx;

    void connectSignalsWithSlots();
};

#endif // DETAILLISTVIEW_H

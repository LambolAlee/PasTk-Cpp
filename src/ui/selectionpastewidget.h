#ifndef SELECTIONPASTEWIDGET_H
#define SELECTIONPASTEWIDGET_H

#include <QWidget>

namespace Ui {
class SelectionPasteWidget;
}

class QAbstractItemModel;
class PasteUtil;
class DataManager;
class Segments;

class SelectionPasteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionPasteWidget(QWidget *parent = nullptr);
    ~SelectionPasteWidget();

    void renderText(bool use_template);
    void selectTemplate(Segments *seg);
    void prepare(bool use_template);
    void finish() { m_activated = false; }

private slots:
    void paste();
    void preview(const QModelIndex &index);

private:
    void connectSignalsWithSlots();
    void renderText();

private:
    Ui::SelectionPasteWidget *ui;
    PasteUtil *m_paste;
    DataManager *m_datamanager;
    Segments *m_seg;

    bool m_use_template;
    bool m_activated;
};

#endif // SELECTIONPASTEWIDGET_H

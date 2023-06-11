#ifndef ITEMEDITORDIALOG_H
#define ITEMEDITORDIALOG_H

#include <QDialog>
#include <QModelIndex>


namespace Ui {
class ItemEditorDialog;
}

enum EditorMode {
    Edit,
    Add,
};

class ItemEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemEditorDialog(QWidget *parent = nullptr);
    ~ItemEditorDialog();

    void edit(const QModelIndex &index);
    void add(bool before);

signals:
    void updateIndex(const QModelIndex &index, const QString &data);
    void submitData(const QString &data, bool before);
    void editFinished();

// QDialog interface
public slots:
    void accept() override;

private:
    Ui::ItemEditorDialog *ui;
    QModelIndex m_currentEditedIndex;
    bool m_textChanged;
    bool m_before;
    EditorMode m_mode;

    void connectSignalsWithSlots();

// QWidget interface
protected:
    void hideEvent(QHideEvent *event) override;
};

#endif // ITEMEDITORDIALOG_H

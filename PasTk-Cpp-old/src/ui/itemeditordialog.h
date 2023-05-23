#ifndef ITEMEDITORDIALOG_H
#define ITEMEDITORDIALOG_H

#include <QDialog>
#include <QModelIndex>


namespace Ui {
class ItemEditorDialog;
}

class ItemEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemEditorDialog(QWidget *parent = nullptr);
    ~ItemEditorDialog();

    void edit(const QModelIndex &index);

signals:
    void updateIndex(const QModelIndex &index, const QString &data);

// QDialog interface
public slots:
    void accept() override;

private:
    Ui::ItemEditorDialog *ui;
    QModelIndex _currentEditedIndex;
    bool _textChanged;

    void connectSignalsWithSlots();
};

#endif // ITEMEDITORDIALOG_H

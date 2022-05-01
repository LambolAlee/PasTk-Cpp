#include "itemeditordialog.h"
#include "ui_itemeditordialog.h"


ItemEditorDialog::ItemEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditorDialog),
    _textChanged(false)
{
    ui->setupUi(this);
    setWindowTitle(QLatin1String("Edit Item Data"));

    connectSignalsWithSlots();
}

ItemEditorDialog::~ItemEditorDialog()
{
    delete ui;
}

void ItemEditorDialog::connectSignalsWithSlots()
{
    connect(ui->textEdit, &QTextEdit::textChanged, this, [=]{_textChanged = true;});
}

void ItemEditorDialog::edit(const QModelIndex &index)
{
    _currentEditedIndex = index;
    ui->textEdit->setText(index.data().toString());
    _textChanged = false;
    open();
}

void ItemEditorDialog::accept()
{
    if (_textChanged) {
        emit updateIndex(_currentEditedIndex, ui->textEdit->toPlainText());
        _textChanged = false;
    }
    return QDialog::accept();
}

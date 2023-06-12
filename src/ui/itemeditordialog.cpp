#include "itemeditordialog.h"
#include "ui_itemeditordialog.h"


ItemEditorDialog::ItemEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditorDialog),
    m_textChanged(false)
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
    connect(ui->textEdit, &QTextEdit::textChanged, this, [this]{m_textChanged = true;});
}

void ItemEditorDialog::hideEvent(QHideEvent *event)
{
    emit editFinished();
    return QDialog::hideEvent(event);
}

void ItemEditorDialog::edit(const QModelIndex &index)
{
    m_mode = EditorMode::Edit;
    m_currentEditedIndex = index;
    ui->textEdit->setText(index.data().toString());
    ui->textEdit->selectAll();
    ui->textEdit->setFocus();
    m_textChanged = false;
    open();
}

void ItemEditorDialog::add(bool before)
{
    m_mode = EditorMode::Add;
    m_before = before;
    ui->textEdit->clear();
    open();
}

void ItemEditorDialog::accept()
{
    switch (m_mode) {

    case Edit:
        if (m_textChanged) {
            emit updateIndex(m_currentEditedIndex, ui->textEdit->toPlainText());
            m_textChanged = false;
        }
        break;
    case Add:
        auto text = ui->textEdit->toPlainText();
        if (!text.isEmpty())
            emit submitData(text, m_before);
        break;
    }

    return QDialog::accept();
}

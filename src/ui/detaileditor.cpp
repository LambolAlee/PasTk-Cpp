#include "detaileditor.h"
#include "ui_detaileditor.h"

DetailEditor::DetailEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetailEditor)
{
    ui->setupUi(this);
}

DetailEditor::~DetailEditor()
{
    delete ui;
}

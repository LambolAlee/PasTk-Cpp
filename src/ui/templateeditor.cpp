#include "templateeditor.h"
#include "ui_templateeditor.h"

TemplateEditor::TemplateEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateEditor)
{
    ui->setupUi(this);
}

TemplateEditor::~TemplateEditor()
{
    delete ui;
}

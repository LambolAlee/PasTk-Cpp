#include "templateeditor.h"
#include "ui_templateeditor.h"
#include "templateinfowidget.h"
#include "templateselectorpanel.h"


TemplateEditor::TemplateEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplateEditor),
    _infoWidget(new TemplateInfoWidget(this)),
    _selectorPanel(new TemplateSelectorPanel(this))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->layout->addWidget(_selectorPanel);
    ui->layout->addWidget(_infoWidget, 1);
}

TemplateEditor::~TemplateEditor()
{
    delete ui;
}

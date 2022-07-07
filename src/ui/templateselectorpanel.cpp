#include "templateselectorpanel.h"
#include "ui_templateselectorpanel.h"

TemplateSelectorPanel::TemplateSelectorPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateSelectorPanel)
{
    ui->setupUi(this);
}

TemplateSelectorPanel::~TemplateSelectorPanel()
{
    delete ui;
}

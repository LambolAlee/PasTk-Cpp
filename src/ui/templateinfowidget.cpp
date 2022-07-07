#include "templateinfowidget.h"
#include "ui_templateinfowidget.h"

TemplateInfoWidget::TemplateInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateInfoWidget)
{
    ui->setupUi(this);
}

TemplateInfoWidget::~TemplateInfoWidget()
{
    delete ui;
}

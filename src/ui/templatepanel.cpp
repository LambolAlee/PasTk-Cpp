#include "templatepanel.h"
#include "ui_templatepanel.h"


TemplatePanel::TemplatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplatePanel),
    _mergeChar("")
{
    ui->setupUi(this);

    connectSignalsWithSlots();
}

TemplatePanel::TemplatePanel(bool mergeOption, QWidget *parent)
    : TemplatePanel(parent)
{
    int id = 1;
    // id = 1 -> on
    // id = 0 -> off
    for (auto &&btn: ui->templateOption->buttons())
        ui->templateOption->setId(btn, id--);
    connect(ui->templateOption, &QButtonGroup::idClicked, ui->templatesCB, &QComboBox::setEnabled);
    if (!mergeOption) {
        ui->mergeWidget->hide();
    }
}

TemplatePanel::~TemplatePanel()
{
    delete ui;
}

void TemplatePanel::connectSignalsWithSlots()
{
}

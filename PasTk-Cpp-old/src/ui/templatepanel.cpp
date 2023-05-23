#include "templatepanel.h"
#include "ui_templatepanel.h"
#include "util/config.h"


TemplatePanel::TemplatePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplatePanel),
    _mergeChar("")
{
    ui->setupUi(this);
    listTemplates();

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
    } else {
        connect(ui->mergeLE, &QLineEdit::returnPressed, this, &TemplatePanel::emitStateAndTemplateChangedSig);
    }
}

TemplatePanel::~TemplatePanel()
{
    delete ui;
}

QPair<int, QString> TemplatePanel::getInfo()
{
    return {ui->templateOption->checkedId(), ui->templatesCB->currentText()};
}

QString TemplatePanel::getMergeStr()
{
    return ui->mergeLE->text();
}

void TemplatePanel::emitStateAndTemplateChangedSig()
{
    if (ui->mergeWidget->isVisible()) {
        emit stateAndTemplateChanged(getMergeStr(), getInfo());
    } else {
        emit stateAndTemplateChanged(getInfo());
    }
}

void TemplatePanel::listTemplates()
{
    Config config;
    config.loadTemplates();
    ui->templatesCB->addItems(config.getTemplatesNames());
    ui->templatesCB->setCurrentText(config.getDefaultTemplate().first);
}

void TemplatePanel::connectSignalsWithSlots()
{
    connect(ui->templateOption, &QButtonGroup::idClicked, this, &TemplatePanel::emitStateAndTemplateChangedSig);
    connect(ui->templatesCB, &QComboBox::currentTextChanged, this, &TemplatePanel::emitStateAndTemplateChangedSig);
}

bool TemplatePanel::isTemplateEnabled()
{
    return ui->templateOption->checkedId();
}

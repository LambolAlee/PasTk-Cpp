#include "plugindetaildialog.h"
#include "ui_plugindetaildialog.h"
#include "formatter/pluginmanager.h"


PluginDetailDialog::PluginDetailDialog(PluginInfo info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDetailDialog)
{
    ui->setupUi(this);

    ui->nameLabel->setText(info.name);
    ui->versionLabel->setText(info.version);
    ui->authorLabel->setText(info.author);
    ui->urlLabel->setText(info.url);
    ui->pathLabel->setText(info.path);
    ui->descriptionText->setText(info.description);
}

PluginDetailDialog::~PluginDetailDialog()
{
    delete ui;
}

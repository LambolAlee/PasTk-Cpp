#include "templateinfowidget.h"
#include "formatter/processor.h"
#include "ui_templateinfowidget.h"
#include "util/config.h"
#include "formatter/pluginmanager.h"

#include <QModelIndex>
#include <QMessageBox>


TemplateInfoWidget::TemplateInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateInfoWidget),
    _editNewItem(false),
    _modified(false),
    _config(new Config)
{
    ui->setupUi(this);
    _config->loadTemplates();
    PluginManager::instance().pluginsProcessor()->reset();

    connectSignalsWithSlots();
}

TemplateInfoWidget::~TemplateInfoWidget()
{
    delete _config;
    delete ui;
}

void TemplateInfoWidget::addTag(const QString &tag)
{
    ui->templateEdit->textCursor().insertText(tag);
}

void TemplateInfoWidget::showTemplate(const QModelIndex &index)
{
    if (!index.isValid()) return;

    _currentEditedName = index.data().toString();
    fillPage();
}

void TemplateInfoWidget::initForNewTemplate()
{
    clearAll();
    ui->nameLE->setFocus();
    ui->nameLE->setText("Enter a name here...");
    ui->nameLE->selectAll();
    _editNewItem = true;
}

void TemplateInfoWidget::deleteItem(const QString &name)
{
    clearAll();
    _config->remove(name);
}

void TemplateInfoWidget::clearAll()
{
    ui->nameLE->clear();
    ui->descriptionEdit->clear();
    ui->templateEdit->clear();
    ui->dataEdit->clear();
    ui->resultText->clear();
}

void TemplateInfoWidget::saveConfig()
{
    _config->saveTemplates();
}

void TemplateInfoWidget::save()
{
    if (!_editNewItem && _currentEditedName.isEmpty())
        return;

    if (ui->nameLE->text().isEmpty()) {
        QMessageBox::warning(this, "Alert", "Template name cannot be empty");
        return;
    }

    if (_editNewItem || _currentEditedName != ui->nameLE->text()) {
        if (_config->contains(ui->nameLE->text())) {
            QMessageBox::warning(this, "Alert", "The name is used. Saving failed");
            return;
        }
    }

    if (_editNewItem) {
        emit newItemSaved(ui->nameLE->text());
        _editNewItem = false;
    }

    _config->setTemplate(ui->nameLE->text(), ui->templateEdit->toPlainText(), ui->descriptionEdit->toPlainText());
    if (_currentEditedName != ui->nameLE->text()) {
        emit itemRenamed(_currentEditedName, ui->nameLE->text());
        _config->remove(_currentEditedName);
    }
//    _currentEditedName.clear();
}

void TemplateInfoWidget::reset()
{
    if (_editNewItem)
        initForNewTemplate();
    else if (!_currentEditedName.isEmpty()) {
        fillPage();
    }
}

void TemplateInfoWidget::setDefaultTemplate()
{
    if (_modified) {
        if (QMessageBox::question(this, "Set Default Template", "Before setting the default template, you should save the changes") == QMessageBox::Yes) {
            save();
        } else return;
    }
    emit defaultTemplateSet();
}

void TemplateInfoWidget::applyTemplate()
{
    auto data = ui->dataEdit->text();
    auto *processor = PluginManager::instance().pluginsProcessor();
    processor->parse(ui->templateEdit->toPlainText());
    ui->resultText->setText(processor->yield(data));
}

void TemplateInfoWidget::fillPage()
{
    auto [templateString, description] = _config->getTemplate(_currentEditedName);
    ui->nameLE->setText(_currentEditedName);
    ui->templateEdit->setText(templateString);
    ui->descriptionEdit->setText(description);
}

void TemplateInfoWidget::connectSignalsWithSlots()
{
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TemplateInfoWidget::save);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, this, &TemplateInfoWidget::reset);
    connect(ui->setDefaultButton, &QPushButton::clicked, this, &TemplateInfoWidget::setDefaultTemplate);
    connect(ui->dataEdit, &QLineEdit::returnPressed, this, &TemplateInfoWidget::applyTemplate);
}

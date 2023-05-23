#include "templateselectorpanel.h"
#include "ui_templateselectorpanel.h"
#include "util/config.h"

#include <QMenu>
#include <QContextMenuEvent>


TemplateSelectorPanel::TemplateSelectorPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateSelectorPanel),
    _config(new Config)
{
    ui->setupUi(this);
    ui->listView->setAlternatingRowColors(true);

    _config->loadTemplates();
    initTemplateList();
    connectSignalsWithSlots();
}

TemplateSelectorPanel::~TemplateSelectorPanel()
{
    delete _config;
    delete ui;
}

void TemplateSelectorPanel::onNewItemSaved(const QString &name)
{
    _temp->setText(name);
    _temp = nullptr;
}

void TemplateSelectorPanel::rename(const QString &oldName[[maybe_unused]], const QString &newName)
{
    auto *item = _model.itemFromIndex(ui->listView->currentIndex());
    item->setText(newName);
}

void TemplateSelectorPanel::createNewTemplate()
{
    if (_temp) return;
    _temp = new QStandardItem("Please Enter a name for it");
    _model.appendRow(_temp);
    ui->listView->setCurrentIndex(_model.indexFromItem(_temp));
    emit newTemplate();
}

void TemplateSelectorPanel::deleteTemplate()
{
    auto index = ui->listView->currentIndex();
    emit clearInfo(index.data().toString());
    _model.removeRow(index.row());
}

void TemplateSelectorPanel::setDefaultTemplate()
{
    auto index = ui->listView->currentIndex();
    if (index.data(Qt::UserRole +1).toBool()) return;

    auto old = _config->getDefaultTemplate().first;
    _config->setDefaultTemplate(index.data().toString());
    if (!old.isEmpty()) {
        auto oldDefault = _model.findItems(old);
        highlightDefault(oldDefault.first(), false);
    }
    highlightDefault(index, true);
}

void TemplateSelectorPanel::unsetDefaultTemplate()
{
    auto index = ui->listView->currentIndex();
    if (!index.data(Qt::UserRole +1).toBool()) return;

    _config->setDefaultTemplate(QString());
    highlightDefault(index, false);
}

void TemplateSelectorPanel::initTemplateList()
{
    auto defaultName = _config->getDefaultTemplate().first;
    for (auto &&name: _config->getTemplatesNames()) {
        QStandardItem *item = new QStandardItem(name);
        if (name == defaultName && !defaultName.isEmpty())
            highlightDefault(item, true);
        _model.appendRow(item);
    }
    ui->listView->setModel(&_model);
}

void TemplateSelectorPanel::connectSignalsWithSlots()
{
    connect(ui->listView, &QListView::clicked, this, &TemplateSelectorPanel::click);
    connect(ui->actionNew, &QAction::triggered, this, &TemplateSelectorPanel::createNewTemplate);
    connect(ui->actionDelete, &QAction::triggered, this, &TemplateSelectorPanel::deleteTemplate);
    connect(ui->actionSet_Default, &QAction::triggered, this, &TemplateSelectorPanel::setDefaultTemplate);
    connect(ui->actionUnset_Default, &QAction::triggered, this, &TemplateSelectorPanel::unsetDefaultTemplate);
}

void TemplateSelectorPanel::highlightDefault(QStandardItem *item, bool state)
{
    item->setData(state);
    auto f = item->font();
    f.setBold(state);
    item->setFont(f);
    if (state)
        item->setIcon(QIcon(":/icons/star.svg"));
    else
        item->setIcon(QIcon());
}

void TemplateSelectorPanel::highlightDefault(const QModelIndex &index, bool state)
{
    highlightDefault(_model.itemFromIndex(index), state);
}

void TemplateSelectorPanel::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(ui->actionNew);
    if (auto index = ui->listView->indexAt(event->pos()); index.isValid()) {
        menu.addAction(ui->actionDelete);
        menu.addSeparator();
        if (index.data(Qt::UserRole +1).toBool())
            menu.addAction(ui->actionUnset_Default);
        else
            menu.addAction(ui->actionSet_Default);
    }
    menu.exec(event->globalPos());
}

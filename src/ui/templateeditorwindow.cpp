#include "templateeditorwindow.h"
#include "ui_templateeditorwindow.h"
#include "templateeditorpanel.h"
#include "tagsdrawercontent.h"
#include "templatelistdelegate.h"


TemplateEditorWindow::TemplateEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplateEditorWindow)
{
    ui->setupUi(this);
    m_panel = new TemplateEditorPanel(this);
    m_content = new TagsDrawerContent(this);
    m_content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delete ui->centralwidget->layout()->replaceWidget(ui->editPanel, m_panel);
    ui->tagDrawer->setVisible(false);
    ui->tagDrawer->setWidget(m_content);
    ui->tagDrawer->setFeatures(QDockWidget::NoDockWidgetFeatures);
    ui->templateDrawer->setFeatures(QDockWidget::NoDockWidgetFeatures);
    ui->templateList->setItemDelegate(new TemplateListDelegate);

    initTemplateListContent();
    connectSignalsWithSlots();
}

TemplateEditorWindow::~TemplateEditorWindow()
{
    delete ui;
}

void TemplateEditorWindow::showWindow(bool with_apply)
{
    m_panel->showApplyButton(with_apply);
    show();
}

void TemplateEditorWindow::initTemplateListContent()
{
    m_config.loadTemplates();
    auto default_template = m_config.getDefaultTemplate();
    for (auto &&name : m_config.getTemplateNameList()) {
        QListWidgetItem *item = new QListWidgetItem(ui->templateList);
        item->setText(name);
        item->setData(Qt::UserRole, name == default_template.first);
        ui->templateList->addItem(item);
        if (name == default_template.first)
            ui->templateList->setCurrentItem(item);
    }
    auto *item = ui->templateList->currentItem();
    m_previous = item;
    m_panel->selectTemplate(item->text(), item->data(Qt::UserRole).toBool());
}

void TemplateEditorWindow::connectSignalsWithSlots()
{
    connect(m_panel, &TemplateEditorPanel::toggleTagDrawer, ui->tagDrawer, &QDockWidget::setVisible);
    connect(m_panel, &TemplateEditorPanel::deleteActionTriggered, this, &TemplateEditorWindow::deleteTemplate);
    connect(ui->templateList, &QListWidget::itemClicked, this, &TemplateEditorWindow::selectItem);
    connect(m_panel, &TemplateEditorPanel::newTemplateCreated, this, &TemplateEditorWindow::addNewTemplate);
    connect(m_panel, &TemplateEditorPanel::templateModified, this, &TemplateEditorWindow::modifyTemplate);
    connect(m_panel, &TemplateEditorPanel::defaultTemplateChanged, this, &TemplateEditorWindow::changeDefaultTemplate);
    connect(m_content, &TagsDrawerContent::tagToBePasted, m_panel, &TemplateEditorPanel::pasteSelectedTag);
    connect(m_panel, &TemplateEditorPanel::templateSelected, this, &TemplateEditorWindow::deliverTemplate);
}

void TemplateEditorWindow::deleteTemplate(bool refresh_default)
{
    QListWidgetItem *templateItem = ui->templateList->currentItem();
    ui->templateList->removeItemWidget(templateItem);
    delete templateItem;

    if (refresh_default) {
        templateItem = new QListWidgetItem(ui->templateList);
        auto pair = m_config.getDefaultTemplate();
        templateItem->setText(pair.first);
        templateItem->setData(Qt::UserRole, true);
        ui->templateList->addItem(templateItem);
    } else {
        templateItem = ui->templateList->currentItem();
    }
    m_previous = templateItem;
    ui->templateList->setCurrentItem(templateItem);
    m_panel->selectTemplate(templateItem->text(), templateItem->data(Qt::UserRole).toBool());
}

void TemplateEditorWindow::modifyTemplate(const TemplatePair &pair)
{
    QListWidgetItem *templateItem = ui->templateList->currentItem();
    templateItem->setText(pair.first);
}

void TemplateEditorWindow::selectItem(QListWidgetItem *current)
{
    m_previous = current;
    m_panel->selectTemplate(current->text(), current->data(Qt::UserRole).toBool());
}

void TemplateEditorWindow::addNewTemplate(const TemplatePair &pair)
{
    QListWidgetItem *item = new QListWidgetItem(ui->templateList);
    item->setText(pair.first);
    ui->templateList->addItem(item);
    m_previous = item;
    ui->templateList->setCurrentItem(item);
}

void TemplateEditorWindow::changeDefaultTemplate(const QString &current, const QString &previous)
{
    auto previous_list = ui->templateList->findItems(previous, Qt::MatchFixedString);
    auto current_list = ui->templateList->findItems(current, Qt::MatchFixedString);
    previous_list.first()->setData(Qt::UserRole, false);
    current_list.first()->setData(Qt::UserRole, true);
}

void TemplateEditorWindow::deliverTemplate(bool changed)
{
    QListWidgetItem *templateItem = ui->templateList->currentItem();
    emit templateSelected(changed, templateItem->text());
    close();
}

#include "templateeditor.h"
#include "ui_templateeditor.h"
#include "templateinfowidget.h"
#include "templateselectorpanel.h"
#include "formatter/pluginmanager.h"

#include <QPluginLoader>
#include <QLabel>
#include <QToolButton>


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
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dockWidget->setTitleBarWidget(new QLabel("Tags"));
    ui->dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    _tagDockBtn = new QToolButton(this);
    _tagDockBtn->setIcon(QIcon(":/icons/right-bar.svg"));
    _tagDockBtn->setCheckable(true);
    _tagDockBtn->setChecked(true);
    _tagDockBtn->setAutoRaise(true);
    ui->statusbar->addPermanentWidget(_tagDockBtn);
    ui->statusbar->setSizeGripEnabled(false);

    initHelpDock();
    connectSignalsWithSlots();
}

TemplateEditor::~TemplateEditor()
{
    delete ui;
}

void TemplateEditor::initHelpDock()
{
    QStandardItem *item = new QStandardItem;
    item->setText("<data>");
    item->setData("The tag represent the raw data you copied");
    _model.appendRow(item);

    auto plist = PluginManager::instance().plugins();
    for (auto &&loader: plist)
        loadPluginHelp(loader);
    ui->listView->setModel(&_model);
}

void TemplateEditor::loadPluginHelp(QPluginLoader *loader)
{
    auto data = loader->metaData().value("MetaData").toObject().value("help").toObject();
    auto end = data.constEnd();
    for (auto begin=data.begin(); begin != end; ++begin) {
        QStandardItem *item = new QStandardItem;
        item->setText(begin.key());
        item->setData(begin.value().toString());
        _model.appendRow(item);
    }
}

void TemplateEditor::connectSignalsWithSlots()
{
    connect(ui->listView, &QListView::activated, this, &TemplateEditor::addTag);
    connect(ui->listView, &QListView::clicked, this, &TemplateEditor::showHelp);
    connect(_tagDockBtn, &QToolButton::toggled, this, &TemplateEditor::toggleTagDock);
    connect(_selectorPanel, &TemplateSelectorPanel::click, _infoWidget, &TemplateInfoWidget::showTemplate);
    connect(_selectorPanel, &TemplateSelectorPanel::newTemplate, _infoWidget, &TemplateInfoWidget::initForNewTemplate);
    connect(_infoWidget, &TemplateInfoWidget::newItemSaved, _selectorPanel, &TemplateSelectorPanel::onNewItemSaved);
    connect(_selectorPanel, &TemplateSelectorPanel::clearInfo, _infoWidget, &TemplateInfoWidget::deleteItem);
    connect(_infoWidget, &TemplateInfoWidget::defaultTemplateSet, _selectorPanel, &TemplateSelectorPanel::setDefaultTemplate);
    connect(_infoWidget, &TemplateInfoWidget::itemRenamed, _selectorPanel, &TemplateSelectorPanel::rename);
}

void TemplateEditor::showHelp(const QModelIndex &index)
{
    if (!index.isValid()) return;
    ui->helpContent->setText(index.data(Qt::UserRole +1).toString());
}

void TemplateEditor::addTag(const QModelIndex &index)
{
    if (!index.isValid()) return;
    _infoWidget->addTag(index.data().toString());
}

void TemplateEditor::toggleTagDock(bool state)
{
    ui->dockWidget->setVisible(state);
}

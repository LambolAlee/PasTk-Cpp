#include "templateeditorpanel.h"
#include "ui_templateeditorpanel.h"
#include <QDialogButtonBox>
#include <QMessageBox>


TemplateEditorPanel::TemplateEditorPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplateEditorPanel),
    m_star_blank(QIcon(":/star_blank.svg")),
    m_star(QIcon(":/star.svg"))
{
    ui->setupUi(this);
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->toolBar->addAction(ui->actionFavor);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addAction(ui->actionOpen_Drawer);
    setFavorState(false);

    m_current_template = {{QStringLiteral(""), QStringLiteral("")}, false};

    connectSignalsWithSlots();
}

TemplateEditorPanel::~TemplateEditorPanel()
{
    delete ui;
}

void TemplateEditorPanel::selectTemplate(const TemplatePair &templatePair, bool favor)
{
    m_addition = false;
    ui->actionAdd->setChecked(false);
    fillWithTemplatePair(templatePair, favor);
}

void TemplateEditorPanel::selectTemplate(const QString &templateName, bool favor)
{
    m_addition = false;
    ui->actionAdd->setChecked(false);
    fillWithTemplatePair(m_config.getTemplate(templateName), favor);
}

void TemplateEditorPanel::pasteSelectedTag(const QString &tag)
{
    ui->templateEdit->insertPlainText(tag);
}

void TemplateEditorPanel::fillWithTemplatePair(const TemplatePair &templatePair, bool favor)
{
    m_current_template = {templatePair, favor};
    ui->nameEdit->setText(templatePair.first);
    ui->templateEdit->setText(templatePair.second);
    setFavorState(favor);
}

void TemplateEditorPanel::initPanelContent()
{
    ui->nameEdit->clear();
    setFavorState(false);
    ui->templateEdit->clear();
}

void TemplateEditorPanel::submit()
{
    if (ui->nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("Template Editor"), QStringLiteral("Template name cannot be left blank!"));
        return;
    }

    TemplatePair pair = {ui->nameEdit->text(), ui->templateEdit->toPlainText()};
    bool favor = ui->actionFavor->data().toBool();

    int same_counter = 0;
    if (m_addition) {
        if (m_config.contains(pair.first)) {
            QMessageBox::warning(this, QStringLiteral("Template Editor"), QStringLiteral("Template name is existed!"));
            return;
        }
        m_config.setTemplate(pair);
        emit newTemplateCreated(pair);
    } else if (pair != m_current_template.first) {
        m_config.setTemplate(pair);
        emit templateModified(pair);
    } else {
        ++same_counter;
    }

    if (favor != m_current_template.second) {
        auto previous = m_config.getDefaultTemplate().first;
        if (favor) {
            m_config.setDefaultTemplate(pair.first);
            emit defaultTemplateChanged(pair.first, previous);
        } else {
            m_config.setDefaultTemplate();
            emit defaultTemplateChanged(m_config.getDefaultTemplate().first, previous);
        }
    } else {
        ++same_counter;
    }

    if (same_counter == 2) {
        ui->statusBar->showMessage(QStringLiteral("No changes saved"), 5000/*ms*/);
    } else {
        ui->statusBar->showMessage(QStringLiteral("Saved Successfully!"), 5000/*ms*/);
        m_addition = false;
    }
    m_current_template = {pair, favor};
    ui->actionAdd->setChecked(false);
}

void TemplateEditorPanel::restore()
{
    if (m_addition)
        initPanelContent();
    else
        fillWithTemplatePair(m_current_template.first, m_current_template.second);
}

void TemplateEditorPanel::connectSignalsWithSlots()
{
    connect(ui->actionOpen_Drawer, &QAction::toggled, this, &TemplateEditorPanel::toggleTagDrawer);
    connect(ui->actionAdd, &QAction::toggled, this, [this](bool state){
        if (m_addition ^ state) {
            m_addition = state;
            initPanelContent();
        }
    });
    connect(ui->actionDelete, &QAction::triggered, this, [this]{
        if (m_addition) {
            initPanelContent();
        } else {
            if (ui->nameEdit->text().isEmpty()) return;
            bool refresh_default = m_config.remove(m_current_template.first.first);
            emit deleteActionTriggered(refresh_default);
        }
    });
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TemplateEditorPanel::submit);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton *button){
        if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
            submit();
        else    // ui->buttonBox->buttonRole(button) == QDialogButtonBox::ResetRole
            restore();
    });
    connect(ui->actionFavor, &QAction::triggered, this, &TemplateEditorPanel::toggleFavoriteState);
}

void TemplateEditorPanel::setFavorState(bool favor)
{
    ui->actionFavor->setData(favor);
    ui->actionFavor->setIcon(favor ? m_star : m_star_blank);
}

void TemplateEditorPanel::toggleFavoriteState()
{
    bool favor = !ui->actionFavor->data().toBool();
    setFavorState(favor);
}

#include "continuouspastewidget.h"
#include "src/data/datamanager.h"
#include "src/template/segments.h"
#include "src/template/templatemanager.h"
#include "ui_continuouspastewidget.h"
#include "src/paste/pasteutil.h"

ContinuousPasteWidget::ContinuousPasteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContinuousPasteWidget),
    m_datamanager(&DataManager::instance()),
    m_template_manager(&TemplateManager::instance()),
    m_paste(&PasteUtil::instance())
{
    ui->setupUi(this);
    ui->backButton->setDefaultAction(ui->actionBack);
    ui->selectionButton->setEnabled(ui->templateSwitch->isChecked());

    connectSignalsWithSlots();
}

ContinuousPasteWidget::~ContinuousPasteWidget()
{
    delete ui;
    m_seg = nullptr;
}

void ContinuousPasteWidget::prepare()
{
    m_datamanager->castFrom(0);
    if (ui->templateSwitch->isChecked()) {
        m_seg = m_template_manager->loadTemplateSegments("", "");
        m_seg->build(m_datamanager);
    }
    renderText();
}

void ContinuousPasteWidget::connectSignalsWithSlots()
{
    connect(ui->templateSwitch, &QCheckBox::toggled, ui->selectionButton, &QPushButton::setEnabled);
    connect(ui->templateSwitch, &QCheckBox::toggled, this, &ContinuousPasteWidget::renderText);
    connect(ui->backButton, &QPushButton::clicked, this, &ContinuousPasteWidget::backToHome);
    connect(ui->pasteButton, &QPushButton::clicked, this, &ContinuousPasteWidget::paste);
    connect(ui->skipButton, &QPushButton::clicked, this, &ContinuousPasteWidget::skip);
}

void ContinuousPasteWidget::renderText()
{
    if (m_datamanager->isEnd()) {
        emit pasteFinished();
        return;
    }

    if (ui->templateSwitch->isChecked()) {
        ui->previewText->setText(m_seg->data());
    } else {
        ui->previewText->setText(m_datamanager->castCurrent());
    }
}

void ContinuousPasteWidget::paste()
{
    ui->previewText->selectAll();
    ui->previewText->copy();
    m_paste->paste();

    skip();
}

void ContinuousPasteWidget::skip()
{
    m_datamanager->next();
    renderText();
}

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
    m_seg(nullptr),
    m_paste(&PasteUtil::instance()),
    m_use_template(false)
{
    ui->setupUi(this);

    connectSignalsWithSlots();
}

ContinuousPasteWidget::~ContinuousPasteWidget()
{
    delete ui;
    m_seg = nullptr;
}

void ContinuousPasteWidget::prepare(bool use_template)
{
    m_datamanager->castFrom(0);
    renderText(use_template);
}

void ContinuousPasteWidget::selectTemplate(bool changed, const QString &templateName, const QString &templateStr)
{
    if (changed)
        m_template_manager->removeCachedTemplateSegments(templateName);
    m_seg = m_template_manager->loadTemplateSegments(templateName, templateStr);
    m_seg->build(m_datamanager);
    renderText();
}

void ContinuousPasteWidget::connectSignalsWithSlots()
{
    connect(ui->pasteButton, &QPushButton::clicked, this, &ContinuousPasteWidget::paste);
    connect(ui->skipButton, &QPushButton::clicked, this, &ContinuousPasteWidget::skip);
}

void ContinuousPasteWidget::renderText()
{
    if (m_seg && m_use_template) {
        ui->previewText->setText(m_seg->data());
    } else {
        ui->previewText->setText(m_datamanager->castCurrent());
    }
}

void ContinuousPasteWidget::renderText(bool use_template)
{
    if (m_datamanager->isEnd()) {
        emit pasteFinished();
        qDebug() << "over";
        return;
    }

    m_use_template = use_template;
    renderText();
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

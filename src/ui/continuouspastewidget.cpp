#include "continuouspastewidget.h"
#include "src/data/datamanager.h"
#include "src/template/segments.h"
#include "ui_continuouspastewidget.h"
#include "src/paste/pasteutil.h"

ContinuousPasteWidget::ContinuousPasteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContinuousPasteWidget),
    m_datamanager(&DataManager::instance()),
    m_seg(nullptr),
    m_paste(&PasteUtil::instance()),
    m_use_template(false),
    m_activated(false)
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
    m_activated = true;
    m_datamanager->castFrom(0);
    renderText(use_template);
}

void ContinuousPasteWidget::selectTemplate(Segments *seg)
{
    m_seg = seg;
    if (m_activated)
        renderText();
}

void ContinuousPasteWidget::connectSignalsWithSlots()
{
    connect(ui->pasteButton, &QPushButton::clicked, this, &ContinuousPasteWidget::paste);
    connect(ui->skipButton, &QPushButton::clicked, this, &ContinuousPasteWidget::skip);
}

void ContinuousPasteWidget::renderText()
{
    if (m_datamanager->isEnd()) {
        emit pasteFinished();
        return;
    }

    if (m_seg && m_use_template) {
        ui->previewText->setText(m_seg->data());
    } else {
        ui->previewText->setText(m_datamanager->castCurrent());
    }
}

void ContinuousPasteWidget::renderText(bool use_template)
{
    m_use_template = use_template;
    if (m_activated)
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

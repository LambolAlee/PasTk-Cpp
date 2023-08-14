#include "selectionpastewidget.h"
#include "src/template/segments.h"
#include "ui_selectionpastewidget.h"
#include "src/paste/pasteutil.h"
#include "src/data/datamanager.h"

SelectionPasteWidget::SelectionPasteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectionPasteWidget),
    m_paste(&PasteUtil::instance()),
    m_datamanager(&DataManager::instance()),
    m_seg(nullptr),
    m_activated(false)
{
    ui->setupUi(this);
    ui->selectionPasteList->setEditTriggers(QListView::NoEditTriggers);
    ui->selectionPasteList->setAlternatingRowColors(true);
    ui->selectionPasteList->setModel(m_datamanager);

    connectSignalsWithSlots();
}

SelectionPasteWidget::~SelectionPasteWidget()
{
    delete ui;
}

void SelectionPasteWidget::renderText()
{
    if (m_seg && m_use_template) {
        ui->previewText->setText(m_seg->data());
    } else {
        ui->previewText->setText(m_datamanager->castCurrent());
    }
}

void SelectionPasteWidget::renderText(bool use_template)
{
    m_use_template = use_template;
    if (m_activated)
        renderText();
}

void SelectionPasteWidget::selectTemplate(Segments *seg)
{
    m_seg = seg;
    if (m_activated)
        renderText();
}

void SelectionPasteWidget::prepare(bool use_template)
{
    m_activated = true;
    m_use_template = use_template;
    QModelIndex index = m_datamanager->index(0,0);
    ui->selectionPasteList->setCurrentIndex(index);
    preview(index);
}

void SelectionPasteWidget::paste()
{
    ui->previewText->selectAll();
    ui->previewText->copy();
    m_paste->paste();
}

void SelectionPasteWidget::preview(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    if (index.row() != m_datamanager->currentIndex()) {
        m_datamanager->castFrom(index.row());
        renderText();
    }
}

void SelectionPasteWidget::connectSignalsWithSlots()
{
    connect(ui->selectionPasteList, &QListView::clicked, this, &SelectionPasteWidget::preview);
    connect(ui->selectionPasteList, &QListView::doubleClicked, this, &SelectionPasteWidget::paste);
}

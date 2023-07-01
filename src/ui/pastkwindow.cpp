#include "pastkwindow.h"
#include "ui_pastkwindow.h"
#include <QMessageBox>
#include <QActionGroup>

#include "src/utils/windowhelper.h"
#include "bottombar.h"
#include "aboutpastkcpp.h"
#include "src/settings/config.h"
#include "src/data/datamanager.h"
#include "itemeditordialog.h"
#include "templateeditorwindow.h"
#include "continuouspastewidget.h"


PasTkWindow::PasTkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasTkWindow)
    , m_datamanager(&DataManager::instance())
    , m_current_page(ContextIndex::Start)
    , m_pin(QIcon(":/pin.png"))
    , m_unpin(QIcon(":/unpin.png"))
    , m_unfocus(false)
{
    ui->setupUi(this);

    m_editor = new ItemEditorDialog(this);
    m_editor_window = new TemplateEditorWindow(this);
    m_continuous = new ContinuousPasteWidget(this);
    delete ui->continuousLayout->replaceWidget(ui->continuousPasteWidget, m_continuous);


    initModeActions();
    buildBottomBar();

    ui->listView->setModel(m_datamanager);
    m_topmost = false;
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo
    connectSignalsWithSlots();
}

PasTkWindow::~PasTkWindow()
{
    delete ui;
    delete m_bottombar;
    m_datamanager = nullptr;
    m_bottombar = nullptr;
}

const QList<QAction *> PasTkWindow::bottomBarActions()
{
    return m_bottombar->actions();
}

QAction *PasTkWindow::preferencesAction()
{
    return ui->actionSettings;
}

const QMenu *PasTkWindow::toolMenu()
{
    return ui->menuTool;
}

const QMenu *PasTkWindow::helpMenu()
{
    return ui->menuHelp;
}

bool PasTkWindow::topmost() const
{
    return m_topmost;
}

void PasTkWindow::setTopmost(bool value)
{
    m_topmost = value;
}

bool PasTkWindow::unfocus() const
{
    return m_unfocus;
}

void PasTkWindow::setUnfocus(bool value)
{
    m_unfocus = value;
}

void PasTkWindow::showAboutMe()
{
    AboutPasTkCpp *about = new AboutPasTkCpp;
    about->show();
}

void PasTkWindow::switchCopy(bool on)
{
    if (on) {
        switchToPage(ContextIndex::Detail);

        m_datamanager->startCopy();
        m_datamanager->listen();
    } else {
        if (m_datamanager->rowCount() == 0)
            switchToPage(ContextIndex::Start);
        m_datamanager->stop();
        m_datamanager->endCopy();
    }
}

void PasTkWindow::clearSelectedItems()
{
    QModelIndexList indexs;
    int last;
    if (indexs = ui->listView->selectedIndexes(); indexs.length() > 0)
        m_datamanager->remove(indexs);
    else
        return;

    if (m_datamanager->rowCount() == 0)
        return;
    else if (last = indexs.constLast().row(); last == m_datamanager->rowCount())
        ui->listView->setCurrentIndex(m_datamanager->index(m_datamanager->rowCount() -1, 0));
    else
        ui->listView->setCurrentIndex(m_datamanager->index(last, 0));
}

void PasTkWindow::addNewItem(const QString &text, bool before)
{
    auto index = ui->listView->selectedIndexes();
    if (before) {
        if (index.length() > 0) {
            auto idx = index.constLast();
            m_datamanager->insert(idx.row(), text);
            ui->listView->setCurrentIndex(idx);
            return;
        }
    }
    m_datamanager->push(text);
    ui->listView->setCurrentIndex(m_datamanager->index(m_datamanager->rowCount()-1, 0));
}

void PasTkWindow::editSelectedItem()
{
    QModelIndex idx;
    auto index = ui->listView->selectedIndexes();
    idx = index.constLast();
    if (index.length() > 1) {
        ui->listView->setCurrentIndex(idx);
    }
    m_datamanager->stop();
    m_editor->edit(idx);
}

void PasTkWindow::backToHome()
{
    switchToPage(ContextIndex::Detail);
}

void PasTkWindow::connectSignalsWithSlots()
{
    connect(ui->startButton, &QPushButton::clicked, this, [this]{
        emit m_bottombar->switchActionToggled(true);
    });
    connect(ui->actionTopmost, &QAction::toggled, this, [this](bool checked){
        WindowHelper::setTopmost(this, checked);
        ui->actionTopmost->setIcon(checked ? m_pin : m_unpin);
    });
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [this]{QMessageBox::aboutQt(this);});
    connect(ui->actionAbout_PasTk2, &QAction::triggered, this, &PasTkWindow::showAboutMe);
    connect(m_bottombar, &BottomBar::clearAllTriggered, this, [this]{
        m_datamanager->clearAll();
        ui->stackedWidget->setCurrentIndex(ContextIndex::Start);
    });
    connect(m_datamanager, &DataManager::itemCountChange, m_bottombar, &BottomBar::updateCount);
    connect(m_bottombar, &BottomBar::switchActionToggled, this, &PasTkWindow::switchCopy);
    connect(m_bottombar, &BottomBar::clearSelectedItems, this, &PasTkWindow::clearSelectedItems);
    connect(m_bottombar, &BottomBar::startPaste, this, &PasTkWindow::startPaste);
    connect(ui->listView, &DetailView::deleteItem, this, &PasTkWindow::clearSelectedItems);
    connect(ui->listView, &DetailView::editItem, this, &PasTkWindow::editSelectedItem);
    connect(ui->listView, &DetailView::newItemAddManuallyBefore, this, [this]{
        m_datamanager->stop();
        m_editor->add(true);
    });
    connect(ui->listView, &DetailView::newItemAddManuallyAfter, this, [this]{
        m_datamanager->stop();
        m_editor->add(false);
    });
    connect(m_editor, &ItemEditorDialog::updateIndex, this, [this](const QModelIndex &index, const QString &data){
        m_datamanager->setData(index, data);
    });
    connect(m_editor, &ItemEditorDialog::submitData, this, &PasTkWindow::addNewItem);
    connect(m_editor, &ItemEditorDialog::editFinished, this, [this]{
        if (!m_datamanager->isStopped()) {
            m_datamanager->listen();
            qDebug() << "here";
        } else {
            qDebug() << "out";
        }
    });
    connect(ui->actionTemplate_Editor, &QAction::triggered, m_editor_window, &TemplateEditorWindow::show);
    connect(m_continuous, &ContinuousPasteWidget::backToHome, this, &PasTkWindow::backToHome);
}

void PasTkWindow::initModeActions()
{
    int checkedMode = Config().getLastUsedMode();
    int mode = 0;
    m_mode_actions = new QActionGroup(this);
    m_mode_actions->setExclusive(true);
    for (auto &&action: {ui->actionContinuous_Mode, ui->actionSelection_Mode}) {
        action->setData(mode);
        if (mode++ == checkedMode)
            action->setChecked(true);
        m_mode_actions->addAction(action);
    }
}

void PasTkWindow::buildBottomBar()
{
    m_bottombar = new BottomBar(this);
    ui->centralwidget->layout()->addWidget(m_bottombar);
    m_bottombar->setModeActions(m_mode_actions);
    // TODO: when switch to paste we should toggle the two bars to invisible

}

void PasTkWindow::resetWindowState()
{
    emit ui->actionTopmost->toggled(m_topmost);
}

void PasTkWindow::startPaste()
{
    int mode = m_mode_actions->checkedAction()->data().toInt();
    switchToPage(ContextIndex::Paste, mode);

    switch (mode) {
    case 0:     // ContinousMode
        break;
    case 1:     // SelectionMode
        break;
    }
}

void PasTkWindow::switchToPage(ContextIndex index, int mode)
{
    bool in_paste_page = (index != ContextIndex::Paste);
    ui->stackedWidget->setCurrentIndex(index + mode);
    m_bottombar->setEnabled(in_paste_page);
    ui->menubar->setVisible(in_paste_page);
#ifdef Q_OS_WIN
    WindowHelper::setWindowUnfocusable(this, !in_paste_page);
#endif
}

void PasTkWindow::showEvent(QShowEvent *event)
{
    resetWindowState();
    return QMainWindow::showEvent(event);
}

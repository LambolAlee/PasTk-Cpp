#include "pastkwindow.h"
#include "qclipboard.h"
#include "src/template/segments.h"
#include "src/template/templatemanager.h"
#include "ui_pastkwindow.h"
#include <QMessageBox>
#include <QActionGroup>

#include "src/utils/windowhelper.h"
#include "bottombar.h"
#include "aboutpastkcpp.h"
#include "src/data/datamanager.h"
#include "itemeditordialog.h"
#include "templateeditorwindow.h"
#include "continuouspastewidget.h"
#include "preferences.h"
#include "selectionpastewidget.h"
#include "src/paste/pasteutil.h"


PasTkWindow::PasTkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasTkWindow)
    , m_datamanager(&DataManager::instance())
    , m_current_page(ContextIndex::Start)
    , m_template_manager(&TemplateManager::instance())
    , m_pin(QIcon(":/pin.png"))
    , m_unpin(QIcon(":/unpin.png"))
    , m_unfocus(false)
{
    ui->setupUi(this);

    m_editor = new ItemEditorDialog(this);
    m_editor_window = new TemplateEditorWindow(this);
    m_continuous = new ContinuousPasteWidget(this);
    m_preferences = new Preferences(this);
    m_selection = new SelectionPasteWidget(this);

    ui->backButton->setDefaultAction(ui->actionBack);
    ui->selectionButton->setEnabled(ui->templateSwitch->isChecked());

    delete ui->continuousLayout->replaceWidget(ui->continuousPasteWidgetPlaceholder, m_continuous);
    delete ui->selectionLayout->replaceWidget(ui->selectionPasteWidgetPlaceholder, m_selection);

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
    m_template_manager = nullptr;
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

void PasTkWindow::linkTrayPasteAction()
{
    if (m_datamanager->rowCount() == 0) return;
    emit m_bottombar->startPaste();
    linkTrayShowAction();
}

void PasTkWindow::linkTrayClearAllAction()
{
    emit m_bottombar->clearAllTriggered();
}

void PasTkWindow::linkTrayShowAction()
{
    show();
    activateWindow();
    raise();
}

void PasTkWindow::showAboutMe()
{
    AboutPasTkCpp *about = new AboutPasTkCpp;
    about->exec();
}

void PasTkWindow::handleSwitchCopy(bool on)
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
    m_continuous->finish();
    m_selection->finish();

    switchToPage(ContextIndex::Detail);
    resetWindowState();
}

void PasTkWindow::quickPaste()
{
    QModelIndex idx;
    auto index = ui->listView->selectedIndexes();
    idx = index.constLast();
    if (idx.isValid()) {
        bool not_in_listening = m_datamanager->isStopped();
        if (!not_in_listening) m_datamanager->stop();
        //qApp->clipboard()->setText(idx.data().toString());
        PasteUtil::instance().paste(this);
        if (!not_in_listening) m_datamanager->listen();
    }
}

void PasTkWindow::connectSignalsWithSlots()
{
    connect(ui->startButton, &QPushButton::clicked, this, [this]{
        emit m_bottombar->switchActionToggled(true);
    });
    connect(ui->actionTopmost, &QAction::toggled, this, [this](bool checked){
        m_topmost = checked;
        WindowHelper::setTopmost(this, checked);
        ui->actionTopmost->setIcon(checked ? m_pin : m_unpin);
    });
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [this]{QMessageBox::aboutQt(this);});
    connect(ui->actionAbout_PasTk2, &QAction::triggered, this, &PasTkWindow::showAboutMe);
    connect(m_bottombar, &BottomBar::clearAllTriggered, this, [this]{
        m_datamanager->clearAll();
        switchToPage(ContextIndex::Start);
    });
    connect(m_datamanager, &DataManager::itemCountChange, m_bottombar, &BottomBar::updateCount);
    connect(m_bottombar, &BottomBar::switchActionToggled, this, &PasTkWindow::handleSwitchCopy);
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
    connect(ui->listView, &DetailView::quickPaste, this, &PasTkWindow::quickPaste);
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
    connect(ui->actionTemplate_Editor, &QAction::triggered, this, [this]{ m_editor_window->showWindow(false); });
    connect(ui->backButton, &QPushButton::clicked, this, &PasTkWindow::backToHome);
    connect(m_continuous, &ContinuousPasteWidget::pasteFinished, this, &PasTkWindow::backToHome);
    connect(ui->actionSettings, &QAction::triggered, m_preferences, &Preferences::exec);
    connect(m_editor_window, &TemplateEditorWindow::templateSelected, this, [this](bool changed, const QString &templateName){
        QString templateStr = m_config.getTemplateStringByName(templateName);
        ui->selectionButton->setText(templateName);
        if (changed)
            m_template_manager->removeCachedTemplateSegments(templateName);
        Segments *seg = m_template_manager->loadTemplateSegments(templateName, templateStr);
        seg->build(m_datamanager);

        m_continuous->selectTemplate(seg);
        m_selection->selectTemplate(seg);
    });

    connect(ui->templateSwitch, &QCheckBox::toggled, ui->selectionButton, &QPushButton::setEnabled);
    connect(ui->templateSwitch, &QCheckBox::toggled, m_continuous, qOverload<bool>(&ContinuousPasteWidget::renderText));
    connect(ui->templateSwitch, &QCheckBox::toggled, m_selection, qOverload<bool>(&SelectionPasteWidget::renderText));
    connect(ui->selectionButton, &QPushButton::clicked, this, [this]{ m_editor_window->showWindow(true); });
}

void PasTkWindow::initModeActions()
{
    int checkedMode = m_config.getLastUsedMode();
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
}

void PasTkWindow::resetWindowState()
{
    if (ui->stackedWidget->currentIndex() == ContextIndex::Paste) {
#ifdef Q_OS_WIN
        WindowHelper::setWindowUnfocusable(this, true);
#endif
    } else {
        emit ui->actionTopmost->toggled(m_topmost);
    }
}

void PasTkWindow::startPaste()
{
    int mode = m_mode_actions->checkedAction()->data().toInt();
    switchToPage(ContextIndex::Paste, mode);
    m_bottombar->switchCopy(false);

    switch (mode) {
    case 0:
        m_continuous->prepare(ui->templateSwitch->isChecked());
        break;
    case 1:
        m_selection->prepare(ui->templateSwitch->isChecked());
        break;
    }
}

void PasTkWindow::switchToPage(ContextIndex index, int mode)
{
    bool in_paste_page = (index != ContextIndex::Paste);
    ui->stackedWidget->setCurrentIndex(index);
    if (index == ContextIndex::Paste)
        ui->pasteModesStack->setCurrentIndex(mode);
    ui->actionTopmost->setEnabled(in_paste_page);
    m_bottombar->setBottomBarEnabled(in_paste_page);
    ui->menubar->setVisible(in_paste_page);
    setWindowUnfocusable(!in_paste_page);
}

void PasTkWindow::setWindowUnfocusable(bool unfocus)
{
    m_unfocus = unfocus;
#ifdef Q_OS_WIN
    WindowHelper::setWindowUnfocusable(this, unfocus);
#endif
}

void PasTkWindow::showEvent(QShowEvent *event)
{
    resetWindowState();
    return QMainWindow::showEvent(event);
}

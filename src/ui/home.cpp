#include "home.h"
#include "ui_home.h"

#include <QMessageBox>
#include <QActionGroup>
#include <QCloseEvent>

#include "util/pasteutil.h"
#include "bottombar.h"
#include "datamanager/datamanager.h"
#include "datamanager/itemdelegate.h"
#include "itemeditordialog.h"
#include "suspendscrollbar.h"
#include "aboutpastkcpp.h"
#include "preferences.h"
#include "util/ghotkeytrigger.h"
#include "util/config.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , _bottomBar(new BottomBar(this))
    , _delegate(new ItemDelegate(this))
    , _editor(new ItemEditorDialog(this))
{
    ui->setupUi(this);
    ui->layout->addWidget(_bottomBar);
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo
    initModeActions();

    auto &dm = DataManager::instance();
    // for test begin
    dm.insert("Hello World");
    dm.insert("wo d shij");
    for (int i=0; i < 100; ++i) {
        dm.insert(QString::number(i));
    }
    _bottomBar->updateCounter();
    // for test end

    ui->detailView->setItemDelegate(_delegate);
    ui->detailView->setModel(dm.model());
    setMinimumSize(QSize(280, 200));

    connectSignalsWithSlots();
    // TODO...
    // as for macOS need to set QAction role
}

Home::~Home()
{
    auto *lastUsedAction = _modeActions->checkedAction();
    Config().setLastUsedMode(lastUsedAction->data().toInt());
    delete ui;
}

const QList<QAction *> Home::bottomBarActions()
{
    return _bottomBar->actions();
}

QAction *Home::preferencesAction()
{
    return ui->actionSettings;
}

void Home::initModeActions()
{
    int checkedMode = Config().getLastUsedMode();
    int mode = 0;
    _modeActions = new QActionGroup(this);
    _modeActions->setExclusive(true);
    for (auto &&action: {ui->actionMerge_Mode, ui->actionContinuous_Mode, ui->actionSelection_Mode}) {
        action->setData(mode);
        if (mode++ == checkedMode)
            action->setChecked(true);
        _modeActions->addAction(action);
    }
    _bottomBar->setModeActions(_modeActions);
}

void Home::connectSignalsWithSlots()
{
    connect(_delegate, &ItemDelegate::doEdit, this, &Home::editOne);
    connect(_delegate, &ItemDelegate::doPaste, this, &Home::pasteOne);
    connect(_delegate, &ItemDelegate::doDelete, this, &Home::deleteOne);

    connect(_bottomBar, &BottomBar::clearItems, this, &Home::clearSelectedItems);
    connect(_bottomBar, &BottomBar::switchState, this, &Home::switchCopy);
    connect(_bottomBar, &BottomBar::startPaste, this, &Home::startPaste);
    connect(_bottomBar, &BottomBar::noData, this, &Home::showHelpContent);

    connect(ui->actionAbout_PasTk_Cpp, &QAction::triggered, this, &Home::showAboutMe);
    connect(ui->actionSettings, &QAction::triggered, this, &Home::openSettingsWindow);
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [=]{QMessageBox::aboutQt(this);});

    connect(_editor, &ItemEditorDialog::updateIndex, this, &Home::setData);
    connect(&_listener, &ClipBoardListner::updateCount, _bottomBar, &BottomBar::updateCounter);
    connect(ui->quickStartBtn, &QPushButton::clicked, _bottomBar, &BottomBar::triggerSwitchAction);
    connect(ui->detailView, &QListView::doubleClicked, this, [=](const QModelIndex &index){editOne(index);});

#ifdef Q_OS_WIN
    PostOffice::instance().upload(this, "home_menu_toggle", SIGNAL(altKeyTriggered()), "altKeyTriggered");
    PostOffice::instance().subscribe(this, "home_menu_toggle", SLOT(toggleMenubar()));
    connect(ui->actionMenu_Bar, &QAction::toggled, this, QOverload<bool>::of(&Home::toggleMenubar));
    connect(&_manager, &PasteManager::pasteOver, this, [=]{PostOffice::instance().post("home_hide_for_paste", Q_ARG(bool, false));});
#endif
}

void Home::toggleMenubar()
{
    if (ui->actionMenu_Bar->isChecked())
        return;
    ui->menubar->setVisible(!ui->menubar->isVisible());
}

void Home::toggleMenubar(bool state)
{
    if (!state)
        ui->menubar->setVisible(state);
}

void Home::editOne(const QModelIndex &index, QAbstractItemModel */*model*/)
{
    _editor->edit(index);
}

void Home::pasteOne(const QModelIndex &index, QAbstractItemModel */*model*/)
{
    PasteUtil::instance().quickPaste(index.data().toString());
}

void Home::deleteOne(const QModelIndex &index, QAbstractItemModel *model)
{
    model->removeRow(index.row());
    _bottomBar->updateCounter();
}

void Home::setData(const QModelIndex &index, const QString &data)
{
    DataManager::instance().setItem(index, data);
}

void Home::clearSelectedItems()
{
    if (!DataManager::instance().count()) {
        QMessageBox::information(this, QLatin1String("Information"), QLatin1String("There is no item going to be cleared."));
        return;
    }
    auto idxList = ui->detailView->selectedIndexes();
    if (idxList.isEmpty()) {
        if (QMessageBox::question(this, QLatin1String("Decision"), QLatin1String("Do you want to remove all the items?")) == QMessageBox::Yes)
            DataManager::instance().clear();
    } else {
        if (QMessageBox::question(this, QLatin1String("Decision"), QLatin1String("Do you want to remove selected items?")) == QMessageBox::Yes)
            DataManager::instance().remove(idxList);
    }
    _bottomBar->updateCounter();
}

void Home::switchCopy(bool state)
{
    if (state) {
        if (Config().getClearAfterNewCopy() == defaults::ClearHistory)
            DataManager::instance().clear();
        _listener.start();
        showDetailContent();
    } else {
        _listener.stop();
        if (DataManager::instance().count() == 0)
            showHelpContent();
    }
}

void Home::showHelpContent()
{
    if (!_listener.isCopying()) {
        ui->stackedWidget->setCurrentIndex(0);
        _bottomBar->setDeleteBtnDisabled(true);
    }
}

void Home::showAboutMe()
{
    AboutPasTkCpp *about = new AboutPasTkCpp(this);
    about->show();
}

void Home::startPaste()
{
    bool needReport = false;
    if (_listener.isCopying()) {
        _listener.stop();
        _bottomBar->triggerSwitchAction();
    }
    if (isVisible()) {
        needReport = true;
        PostOffice::instance().post("home_hide_for_paste", Q_ARG(bool, true));
    }

    auto *action = _modeActions->checkedAction();
    _manager.startPaste(action->data().toInt(), needReport);
}

void Home::openSettingsWindow()
{
    Preferences preferences(this);
    connect(&preferences, &QDialog::accepted, this, [=]{PostOffice::instance().post("update_shortcuts");});
    preferences.exec();
}

void Home::updateUi()
{
    ui->actionMenu_Bar->setChecked(Config().getMenuBarShow());
    toggleMenubar();
}

void Home::showDetailContent()
{
    ui->stackedWidget->setCurrentIndex(1);
    _bottomBar->setDeleteBtnDisabled(false);
}

void Home::showEvent(QShowEvent *event)
{
    updateUi();
    return QWidget::showEvent(event);
}

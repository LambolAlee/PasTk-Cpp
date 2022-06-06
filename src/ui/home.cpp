#include "home.h"
#include "ui_home.h"

#include <QStyle>
#include <QKeyEvent>
#include <QScrollBar>
#include <QMessageBox>
#include <QActionGroup>

#include "util/cframelessbridge.h"
#include "util/pasteutil.h"
#include "bottombar.h"
#include "datamanager/datamanager.h"
#include "datamanager/itemdelegate.h"
#include "itemeditordialog.h"
#include "suspendscrollbar.h"
#include "aboutpastkcpp.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , _bottomBar(new BottomBar(this))
    , _delegate(new ItemDelegate(this))
    , _editor(new ItemEditorDialog(this))
{
    ui->setupUi(this);
    ui->menubar->setVisible(false);
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
    delete ui;
}

void Home::initModeActions()
{
    int mode = 0;
    _modeActions = new QActionGroup(this);
    auto actions = {ui->actionTemplate_Mode, ui->actionContinuous_Mode, ui->actionSelection_Mode};
    for (auto &&action: actions) {
        action->setData(mode++);
        _modeActions->addAction(action);
    }
    _modeActions->setExclusive(true);
    _bottomBar->setModeActions(_modeActions);
}

void Home::connectSignalsWithSlots()
{
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [=]{QMessageBox::aboutQt(this);});
    connect(_delegate, &ItemDelegate::doEdit, this, &Home::editOne);
    connect(_delegate, &ItemDelegate::doPaste, this, &Home::pasteOne);
    connect(_delegate, &ItemDelegate::doDelete, this, &Home::deleteOne);
    connect(ui->detailView, &QListView::doubleClicked, this, [=](const QModelIndex &index){editOne(index);});
    connect(_editor, &ItemEditorDialog::updateIndex, this, &Home::setData);
    connect(_bottomBar, &BottomBar::clearItems, this, &Home::clearSelectedItems);
    connect(_bottomBar, &BottomBar::switchState, this, &Home::switchCopy);
    connect(&_listener, &ClipBoardListner::updateCount, _bottomBar, &BottomBar::updateCounter);
    connect(_bottomBar, &BottomBar::noData, this, &Home::showHelpContent);
    connect(ui->quickStartBtn, &QPushButton::clicked, _bottomBar, &BottomBar::triggerSwitchAction);
    connect(ui->actionAbout_PasTk_Cpp, &QAction::triggered, this, &Home::showAboutMe);
    connect(_bottomBar, &BottomBar::startPaste, this, &Home::startPaste);

#ifdef Q_OS_WIN
    connect(&CFramelessBridge::instance(), &CFramelessBridge::altKeyTriggered, this, QOverload<>::of(&Home::toggleMenubar));
    connect(ui->actionMenu_Bar, &QAction::toggled, this, QOverload<bool>::of(&Home::toggleMenubar));
    connect(&_manager, &PasteManager::pasteOver, this, [=]{CFramelessBridge::instance().emitHideForPaste(false);});
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
        CFramelessBridge::instance().emitHideForPaste(true);
    }

    auto *action = _modeActions->checkedAction();
    _manager.startPaste(action->data().toInt(), needReport);
}

void Home::showDetailContent()
{
    ui->stackedWidget->setCurrentIndex(1);
    _bottomBar->setDeleteBtnDisabled(false);
}

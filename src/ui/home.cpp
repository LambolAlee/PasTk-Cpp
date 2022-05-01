#include "home.h"
#include "ui_home.h"

#include <QStyle>
#include <QKeyEvent>
#include <QScrollBar>
#include <QMessageBox>

#include "util/cframelessbridge.h"
#include "util/pasteutil.h"
#include "bottombar.h"
#include "datamanager/datamanager.h"
#include "datamanager/itemdelegate.h"
#include "itemeditordialog.h"


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

    auto &dm = DataManager::instance();
    // for test begin
    dm.insert("Hello World");
    dm.insert("wo d shij");
    for (int i=0; i < 4; ++i) {
        dm.insert(QString::number(i));
    }
    _bottomBar->updateCounter();
    // for test end
    ui->detailView->setItemDelegate(_delegate);
    ui->detailView->setModel(dm.model());
    setMinimumSize(QSize(280, 200));

    initDetailView();
    connectSignalsWithSlots();
}

Home::~Home()
{
    delete ui;
}

void Home::connectSignalsWithSlots()
{
    connect(&CFramelessBridge::instance(), &CFramelessBridge::altKeyTriggered, this, &Home::toggleMenubar);
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [=]{QMessageBox::aboutQt(this);});
    connect(_delegate, &ItemDelegate::doEdit, this, &Home::editOne);
    connect(_delegate, &ItemDelegate::doPaste, this, &Home::pasteOne);
    connect(_delegate, &ItemDelegate::doDelete, this, &Home::deleteOne);
    connect(ui->detailView, &QListView::doubleClicked, this, [=](const QModelIndex &index){editOne(index);});
    connect(_editor, &ItemEditorDialog::updateIndex, this, &Home::setData);
    connect(_bottomBar, &BottomBar::clearAllItems, this, [=]{
        if (QMessageBox::question(this, QLatin1String("Decision"), QLatin1String("Do you want to remove all the items?")) == QMessageBox::Yes) {
            DataManager::instance().clear();
            _bottomBar->updateCounter();
        }
    });
    connect(_bottomBar, &BottomBar::switchState, this, &Home::switchCopy);
    connect(&_listner, &ClipBoardListner::updateCount, _bottomBar, &BottomBar::updateCounter);
    connect(_bottomBar, &BottomBar::noData, this, &Home::showHelpContent);
    connect(ui->quickStartBtn, &QPushButton::clicked, _bottomBar, &BottomBar::triggerSwitchAction);
}

void Home::initDetailView()
{
    ui->detailView->setMouseTracking(true);
    ui->detailView->setAlternatingRowColors(true);
    ui->detailView->setSpacing(5);
    ui->detailView->setAutoScroll(false);
    ui->detailView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->detailView->verticalScrollBar()->setSingleStep(15);
    ui->detailView->setEditTriggers(QListView::NoEditTriggers);
}

void Home::toggleMenubar()
{
    ui->menubar->setVisible(!ui->menubar->isVisible());
}

void Home::editOne(const QModelIndex &index, QAbstractItemModel */*model*/)
{
    _editor->edit(index);
}

void Home::pasteOne(const QModelIndex &index, QAbstractItemModel */*model*/)
{
    PasteUtil::instance().paste(index.data().toString());
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

void Home::switchCopy(bool state)
{
    if (state) {
        _listner.start();
        showDetailContent();
    } else {
        _listner.stop();
        if (DataManager::instance().count() == 0)
            showHelpContent();
    }
}

void Home::showHelpContent()
{
    if (!_listner.isCopying())
        ui->stackedWidget->setCurrentIndex(0);
}

void Home::showDetailContent()
{
    ui->stackedWidget->setCurrentIndex(1);
}

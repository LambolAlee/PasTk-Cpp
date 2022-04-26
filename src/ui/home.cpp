#include "home.h"
#include "ui_home.h"

#include <QStyle>
#include <QKeyEvent>
#include <QScrollBar>
#include <QMessageBox>

#include "util/cframelessbridge.h"
#include "bottombar.h"
#include "datamanager/datamanager.h"
#include "datamanager/itemdelegate.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , _bottomBar(new BottomBar(this))
    , _delegate(new ItemDelegate(this))
{
    ui->setupUi(this);
    ui->menubar->setVisible(false);
    ui->layout->addWidget(_bottomBar);
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo

    auto &dm = DataManager::instance();
    dm.insert("Hello World");
    dm.insert("wo d shij");
    for (int i=0; i < 4; ++i) {
        dm.insert(QString::number(i));
    }
    ui->detailView->setItemDelegate(_delegate);
    ui->detailView->setModel(dm.model());

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
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &Home::triggerAboutQtAction);
    connect(_delegate, &ItemDelegate::doEdit, this, &Home::editOne);
}

void Home::initDetailView()
{
    ui->detailView->setMouseTracking(true);
    ui->detailView->setAlternatingRowColors(true);
    ui->detailView->setSpacing(5);
    ui->detailView->setEditTriggers(QListView::NoEditTriggers);
    ui->detailView->setAutoScroll(false);
    ui->detailView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->detailView->verticalScrollBar()->setSingleStep(15);
}

void Home::toggleMenubar()
{
    ui->menubar->setVisible(!ui->menubar->isVisible());
}

void Home::triggerAboutQtAction()
{
    QMessageBox::aboutQt(this);
}

void Home::editOne(QAbstractItemModel *model, const QModelIndex &index)
{

}

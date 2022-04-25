#include "home.h"
#include "ui_home.h"

#include <QStyle>
#include <QKeyEvent>
#include <QMessageBox>

#include "util/cframelessbridge.h"
#include "bottombar.h"
#include "datamanager/datamanager.h"
#include "datamanager/itemdelegate.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , _bottomBar(new BottomBar(this))
{
    ui->setupUi(this);
    ui->menubar->setVisible(false);
    ui->layout->addWidget(_bottomBar);
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo

    auto &dm = DataManager::instance();
    dm.insert("Hello World");
    dm.insert("wo d shij");
    dm.insert("你好");
    dm.insert("你好");
    dm.insert("你好");
    dm.insert("你好");
    ui->detailView->setItemDelegate(new ItemDelegate);
    ui->detailView->setModel(dm.model());

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
}

void Home::toggleMenubar()
{
    ui->menubar->setVisible(!ui->menubar->isVisible());
}

void Home::triggerAboutQtAction()
{
    QMessageBox::aboutQt(this);
}

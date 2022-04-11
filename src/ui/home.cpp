#include "home.h"
#include "ui_home.h"

#include <QStyle>
#include <QKeyEvent>

#include "util/cframelessbridge.h"
#include "bottombar.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , _bottomBar(new BottomBar(this))
{
    ui->setupUi(this);
    ui->menubar->setVisible(false);
    ui->layout->addWidget(_bottomBar);
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo

    connectSignalsWithSlots();
}

Home::~Home()
{
    delete ui;
}

void Home::connectSignalsWithSlots()
{
    connect(&CFramelessBridge::instance(), &CFramelessBridge::altKeyTriggered, this, &Home::toggleMenubar);
}

void Home::toggleMenubar()
{
    ui->menubar->setVisible(!ui->menubar->isVisible());
}

#include "bottombar.h"
#include "ui_bottombar.h"

#include "datamanager/datamanager.h"


BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);

    ui->switchBtn->setDefaultAction(ui->actionSwitch);
    ui->clearAllBtn->setDefaultAction(ui->actionClear);
    ui->pasteBtn->setDefaultAction(ui->actionPaste);

    connectSignalsWithSlots();
}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::triggerSwitchAction()
{
    ui->actionSwitch->toggle();
}

void BottomBar::toggleSwitch(bool state)
{
    if (state) {
        ui->actionSwitch->setIcon(QIcon(":/icons/pause.svg"));
        ui->actionSwitch->setToolTip(QLatin1String("stop listening to the clipboard"));
    } else {
        ui->actionSwitch->setIcon(QIcon(":/icons/play.svg"));
        ui->actionSwitch->setToolTip(QLatin1String("start to listen to the clipboard"));
    }
    emit switchState(state);
}

void BottomBar::updateCounter()
{
    int rows = DataManager::instance().count();
    if (rows == 0)
        emit noData();
    ui->counterLabel->setText(QString::number(rows));
}

void BottomBar::connectSignalsWithSlots()
{
    connect(ui->actionSwitch, &QAction::toggled, this, &BottomBar::toggleSwitch);
    connect(ui->actionPaste, &QAction::triggered, this, &BottomBar::startPaste);
    connect(ui->actionClear, &QAction::triggered, this, &BottomBar::clearItems);
}

#include "bottombar.h"
#include "ui_bottombar.h"

#include "datamanager/datamanager.h"
#include "util/ghotkeytrigger.h"

#include <QMenu>
#include <QActionGroup>


BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);

    ui->switchBtn->setDefaultAction(ui->actionSwitch);
    ui->clearBtn->setDefaultAction(ui->actionClear);
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

void BottomBar::setModeActions(QActionGroup *modeActions)
{
    QMenu *menu = new QMenu(this);
    menu->addActions(modeActions->actions());
    ui->actionPaste->setMenu(menu);
}

void BottomBar::setDeleteBtnDisabled(bool disable)
{
    ui->clearBtn->setDisabled(disable);
}

const QList<QAction *> BottomBar::actions()
{
    return {ui->actionSwitch, ui->actionClear, ui->actionPaste};
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

    auto &trigger = GHotkeyTrigger::instance();
    connect(trigger.value("copy"), &QHotkey::activated, ui->actionSwitch, &QAction::toggle);
    connect(trigger.value("runPaste"), &QHotkey::activated, ui->actionPaste, &QAction::trigger);
}

#include "bottombar.h"
#include "ui_bottombar.h"

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
}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::setModeActions(QActionGroup *group)
{
    QMenu *menu = new QMenu(this);
    menu->addActions(group->actions());
    ui->actionPaste->setMenu(menu);
}

const QList<QAction *> BottomBar::actions()
{
    return {ui->actionSwitch, ui->actionClear, ui->actionPaste};
}

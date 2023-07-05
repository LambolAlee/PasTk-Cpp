#include "bottombar.h"
#include "ui_bottombar.h"

#include <QMenu>
#include <QActionGroup>
#include <QMouseEvent>

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar),
    m_start(QIcon(":/play.svg")),
    m_pause(QIcon(":/pause.svg"))
{
    ui->setupUi(this);

    ui->switchBtn->setDefaultAction(ui->actionSwitch);
    ui->clearBtn->setDefaultAction(ui->actionClear);
    ui->clearBtn->installEventFilter(this);
    ui->clearBtn->setDisabled(true);

    connect(ui->actionSwitch, &QAction::toggled, this, &BottomBar::switchActionToggled);
    connect(this, &BottomBar::switchActionToggled, this, &BottomBar::switchCopy);
    connect(ui->pasteBtn, &QToolButton::clicked, this, &BottomBar::startPaste);
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
    ui->pasteBtn->setDefaultAction(ui->actionPaste);
    ui->pasteBtn->setDisabled(true);
}

const QList<QAction *> BottomBar::actions()
{
    return {ui->actionSwitch, ui->actionClear, ui->actionPaste};
}

void BottomBar::switchCopy(bool on)
{
    ui->actionSwitch->setIcon(on ? m_pause : m_start);
    ui->switchBtn->setChecked(on);
}

void BottomBar::setClearActionDisabled(bool disabled)
{
    ui->actionClear->setDisabled(disabled);
}

void BottomBar::setBottomBarEnabled(bool enabled)
{
    setEnabled(enabled);
    for (auto &&action: {ui->actionClear, ui->actionPaste, ui->actionSwitch})
        action->setEnabled(enabled);
}

bool BottomBar::eventFilter(QObject *watched, QEvent *event)
{
    QToolButton *btn = static_cast<QToolButton *>(watched);
    if (!btn->isEnabled())
        return false;

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
        if (mouse_event->button() == Qt::LeftButton) {
            if (mouse_event->modifiers() == Qt::ShiftModifier)
                emit clearAllTriggered();
            else
                emit clearSelectedItems();
        }
    }
    return false;
}

void BottomBar::updateCount(int count)
{
    ui->countLabel->setText(QString::number(count));

    if (count == 0) {
        if (ui->clearBtn->isEnabled()) {
            ui->clearBtn->setDisabled(true);
            ui->pasteBtn->setDisabled(true);
        }
    } else if (!ui->clearBtn->isEnabled()) {
        ui->clearBtn->setDisabled(false);
        ui->pasteBtn->setDisabled(false);
    }
}

void BottomBar::on_BottomBar_clearAllTriggered() {
    emit switchActionToggled(false);
}

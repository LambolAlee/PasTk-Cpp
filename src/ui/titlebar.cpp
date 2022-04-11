#include "titlebar.h"
#include "ui_titlebar.h"


TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    ui->topmostTB->setProperty("topmost", false);

    connectSignalsWithSlots();
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::connectSignalsWithSlots()
{
    connect(ui->topmostTB, &QToolButton::clicked, this, &TitleBar::topmostButtonToggled);
    connect(ui->minTB, &QToolButton::clicked, this, &TitleBar::minimizeButtonClicked);
    connect(ui->closeTB, &QToolButton::clicked, this, &TitleBar::closeButtonClicked);
}

QLabel *TitleBar::titleWidget()
{
    return ui->titleLabel;
}

void TitleBar::closeButtonClicked()
{
    _bridge.emitClosed();
}

void TitleBar::minimizeButtonClicked()
{
    _bridge.emitMinimized();
}

void TitleBar::topmostButtonToggled()
{
    if (ui->topmostTB->property("topmost").toBool()) {
        // cancel setting the window topmost
        ui->topmostTB->setProperty("topmost", false);
        _bridge.emitTopmost(false);
        ui->topmostTB->setIcon(QIcon(":/icons/unpin.png"));
    } else {
        // set the window the topmost
        ui->topmostTB->setProperty("topmost", true);
        _bridge.emitTopmost(true);
        ui->topmostTB->setIcon(QIcon(":/icons/pin.png"));
    }
}

#include "titlebar.h"
#include "ui_titlebar.h"

#include "util/config.h"


TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);

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
    _poster.post("home_close");
}

void TitleBar::minimizeButtonClicked()
{
    _poster.post("home_minimize");
}

void TitleBar::topmostButtonToggled()
{
    if (ui->topmostTB->property("topmost").toBool()) {
        // cancel setting the window topmost
        ui->topmostTB->setProperty("topmost", false);
        _poster.post("home_topmost", Q_ARG(bool, false));
        ui->topmostTB->setIcon(QIcon(":/icons/unpin.png"));
    } else {
        // set the window the topmost
        ui->topmostTB->setProperty("topmost", true);
        _poster.post("home_topmost", Q_ARG(bool, true));
        ui->topmostTB->setIcon(QIcon(":/icons/pin.png"));
    }
}

void TitleBar::showEvent(QShowEvent *event)
{
    Config config;
    ui->topmostTB->setProperty("topmost", !config.getTopmost());
    topmostButtonToggled();
    return QWidget::showEvent(event);
}

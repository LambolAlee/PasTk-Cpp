#include "continuouspastewidget.h"
#include "ui_continuouspastewidget.h"

ContinuousPasteWidget::ContinuousPasteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContinuousPasteWidget)
{
    ui->setupUi(this);
    ui->backButton->setDefaultAction(ui->actionBack);

    connectSignalsWithSlots();
}

ContinuousPasteWidget::~ContinuousPasteWidget()
{
    delete ui;
}

void ContinuousPasteWidget::connectSignalsWithSlots()
{
    connect(ui->templateSwitch, &QCheckBox::toggled, ui->selectionButton, &QPushButton::setEnabled);
    connect(ui->backButton, &QPushButton::clicked, this, &ContinuousPasteWidget::backToHome);
}

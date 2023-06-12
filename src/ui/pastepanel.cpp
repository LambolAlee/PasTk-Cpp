#include "pastepanel.h"
#include "ui_pastepanel.h"

PastePanel::PastePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PastePanel)
{
    ui->setupUi(this);
}

PastePanel::~PastePanel()
{
    delete ui;
}

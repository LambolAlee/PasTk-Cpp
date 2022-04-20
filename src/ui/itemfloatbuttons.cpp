#include "itemfloatbuttons.h"
#include "ui_itemfloatbuttons.h"

ItemFloatButtons::ItemFloatButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemFloatButtons)
{
    ui->setupUi(this);
}

ItemFloatButtons::~ItemFloatButtons()
{
    delete ui;
}

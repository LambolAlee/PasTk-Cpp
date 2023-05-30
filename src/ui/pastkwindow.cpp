#include "pastkwindow.h"
#include "ui_pastkwindow.h"
#include <QToolButton>
#include <QLabel>

#include "src/paste/pasteutil.h"
#include "bottombar.h"


PasTkWindow::PasTkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasTkWindow)
{
    ui->setupUi(this);
    buildBottomBar();

    connectSignalsWithSlots();
}

PasTkWindow::~PasTkWindow()
{
    delete ui;
    delete m_bottombar;
}

void PasTkWindow::showDetailContent()
{
//    ui->stackedWidget->setCurrentIndex(1);
    PasteUtil::instance().paste(this);
}

void PasTkWindow::connectSignalsWithSlots()
{
    connect(ui->startButton, &QPushButton::clicked, this, &PasTkWindow::showDetailContent);
}

void PasTkWindow::buildBottomBar()
{
    m_bottombar = new BottomBar(this);
    ui->centralwidget->layout()->addWidget(m_bottombar);
}

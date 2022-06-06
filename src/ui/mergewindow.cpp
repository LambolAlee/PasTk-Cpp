#include "mergewindow.h"
#include "ui_mergewindow.h"
#include "templatepanel.h"
#include "util/util.h"


MergeWindow::MergeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MergeWindow),
    _panel(new TemplatePanel(true, this))
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(1, _panel);

#ifdef Q_OS_WIN
    Util::setWindowUnfocusable(this);
#endif

    setWindowTitle("PasTkCpp - Merge Mode");
    resize(320, 420);
    setWindowOpacity(0.8);
    connectSignalsWithSlots();
}

MergeWindow::~MergeWindow()
{
    delete ui;
}

void MergeWindow::connectSignalsWithSlots()
{

}

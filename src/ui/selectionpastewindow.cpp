#include "selectionpastewindow.h"
#include "ui_selectionpastewindow.h"
#include "util/util.h"
#include "templatepanel.h"


SelectionPasteWindow::SelectionPasteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectionPasteWindow),
    _panel(new TemplatePanel(false, this))
{
    ui->setupUi(this);
    ui->listView->setSelectionMode(QAbstractItemView::NoSelection);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(2, _panel);

#ifdef Q_OS_WIN
    Util::setWindowUnfocusable(this);
#endif

    setWindowTitle("PasTkCpp - Selection Mode");
    resize(320, 520);
    setWindowOpacity(0.8);
    connectSignalsWithSlots();
}

SelectionPasteWindow::~SelectionPasteWindow()
{
    delete ui;
}

void SelectionPasteWindow::connectSignalsWithSlots()
{

}

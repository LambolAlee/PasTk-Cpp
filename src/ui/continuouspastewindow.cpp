#include "continuouspastewindow.h"
#include "ui_continuouspastewindow.h"

#include "datamanager/datamanager.h"
#include "templatepanel.h"
#include "util/util.h"


ContinuousPasteWindow::ContinuousPasteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContinuousPasteWindow),
    _dataManager(DataManager::instance()),
    _panel(new TemplatePanel(false, this)),
    _current(0)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(1, _panel);

#ifdef Q_OS_WIN
    Util::setWindowUnfocusable(this);
#endif

    ui->previewBrowser->setText(_dataManager.getItem(_current)->data().toString());
    setWindowTitle("PasTkCpp - Continuous Mode");
    resize(320, 320);
    setWindowOpacity(0.8);
    connectSignalsWithSlots();
}

ContinuousPasteWindow::~ContinuousPasteWindow()
{
    delete ui;
}

void ContinuousPasteWindow::connectSignalsWithSlots()
{
}

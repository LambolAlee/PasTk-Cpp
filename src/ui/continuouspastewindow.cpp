#include "continuouspastewindow.h"
#include "ui_continuouspastewindow.h"

#include "datamanager/datamanager.h"
#include "templatepanel.h"
#include "util/util.h"
#include "util/pasteutil.h"
#include "util/ghotkeytrigger.h"


ContinuousPasteWindow::ContinuousPasteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContinuousPasteWindow),
    _dataManager(DataManager::instance()),
    _panel(new TemplatePanel(false, this)),
    _current(0),
    _endToQuit(false)
{
    ui->setupUi(this);

    _max = _dataManager.count() -1;

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(1, _panel);

#ifdef Q_OS_WIN
    Util::setWindowUnfocusable(this);
#endif

    prepareNextData();
    setWindowTitle("PasTkCpp - Continuous Mode");
    resize(320, 320);
    setWindowOpacity(0.8);
    connectSignalsWithSlots();
}

ContinuousPasteWindow::~ContinuousPasteWindow()
{
    delete ui;
}

void ContinuousPasteWindow::run()
{
    if (_endToQuit) close();
    // need to interact with the template system
    PasteUtil::instance().paste(_currentData, true);
    prepareNextData();
}

void ContinuousPasteWindow::connectSignalsWithSlots()
{
    connect(ui->quitButton, &QPushButton::clicked, this, &ContinuousPasteWindow::close);
    connect(ui->pasteButton, &QPushButton::clicked, this, &ContinuousPasteWindow::run);
    connect(ui->skipButton, &QPushButton::clicked, this, &ContinuousPasteWindow::prepareNextData);

    auto *pasteHotkey = GHotkeyTrigger::instance().value("paste");
    auto *skipHotkey = GHotkeyTrigger::instance().value("skip");
    pasteHotkey->setRegistered(true);
    skipHotkey->setRegistered(true);
    connect(pasteHotkey, &QHotkey::activated, this, &ContinuousPasteWindow::run);
    connect(skipHotkey, &QHotkey::activated, this, &ContinuousPasteWindow::prepareNextData);
}

bool ContinuousPasteWindow::checkForTheEnd()
{
    return _current > _max;
}

void ContinuousPasteWindow::prepareNextData()
{
    if (_endToQuit) close();
    if (checkForTheEnd()) {
        ui->previewBrowser->setText(QStringLiteral("There is no data behind, click any button to quit..."));
        _endToQuit = true;
    } else {
        _currentData = _dataManager.getItem(_current++)->text();
        ui->previewBrowser->setText(_currentData);
    }
}

void ContinuousPasteWindow::closeEvent(QCloseEvent *event)
{
    emit reportQuit();
    GHotkeyTrigger::instance().value("paste")->setRegistered(false);
    GHotkeyTrigger::instance().value("skip")->setRegistered(false);
    return QMainWindow::closeEvent(event);
}

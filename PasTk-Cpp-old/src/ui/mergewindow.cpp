#include "mergewindow.h"
#include "datamanager/datamanager.h"
#include "ui_mergewindow.h"
#include "templatepanel.h"
#include "util/util.h"
#include "util/ghotkeytrigger.h"
#include "util/config.h"
#include "formatter/pluginmanager.h"
#include "formatter/processor.h"
#include "util/pasteutil.h"


MergeWindow::MergeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MergeWindow),
    _panel(new TemplatePanel(true, this)),
    _config(new Config),
    _processor(PluginManager::instance().pluginsProcessor())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(1, _panel);
    ui->previewBrowser->hide();

//#ifdef Q_OS_WIN
//    Util::setWindowUnfocusable(this);
//#endif

    _config->loadTemplates();
    _processor->reset();

    setWindowTitle("PasTkCpp - Merge Mode");
    resize(320, 200);
    setWindowOpacity(0.8);
    connectSignalsWithSlots();
}

MergeWindow::~MergeWindow()
{
    delete _config;
    delete ui;
}

void MergeWindow::run()
{
    QStringList result;
    auto [state, templateName] = _panel->getInfo();
    if (state) {
        auto templateStr = _config->getTemplate(templateName).first;
        _processor->parse(templateStr);
    }
    auto &manager = DataManager::instance();
    auto rowCount = manager.count();
    for (auto i=0; i < rowCount; ++i) {
        auto *item = manager.getItem(i);
        if (state)
            result << _processor->yield(item->text());
        else
            result << item->text();
    }
    QString finalStr;
    auto sep = _panel->getMergeStr();
    finalStr = result.join(sep);
    PasteUtil::instance().paste(this, finalStr);
}

void MergeWindow::connectSignalsWithSlots()
{
    connect(ui->quitButton, &QPushButton::clicked, this, &MergeWindow::close);
    connect(ui->pasteButton, &QPushButton::clicked, this, &MergeWindow::run);

    auto *pasteHotkey = GHotkeyTrigger::instance().value("paste");
    pasteHotkey->setRegistered(true);
    connect(pasteHotkey, &QHotkey::activated, this, &MergeWindow::run);
}

void MergeWindow::closeEvent(QCloseEvent *event)
{
    emit reportQuit();
    GHotkeyTrigger::instance().value("paste")->setRegistered(false);
    return QMainWindow::closeEvent(event);
}

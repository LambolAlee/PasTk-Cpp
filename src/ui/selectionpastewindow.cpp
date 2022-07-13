#include "selectionpastewindow.h"
#include "formatter/processor.h"
#include "ui_selectionpastewindow.h"
#include "util/util.h"
#include "templatepanel.h"
#include "datamanager/itemdelegate.h"
#include "datamanager/datamanager.h"
#include "util/pasteutil.h"
#include "util/config.h"
#include "formatter/pluginmanager.h"

#include <QHoverEvent>
#include <QTimer>


SelectionPasteWindow::SelectionPasteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectionPasteWindow),
    _panel(new TemplatePanel(false, this)),
    _delegate(new ItemDelegate(this, true)),
    _timer(new QTimer(this)),
    _config(new Config),
    _processor(PluginManager::instance().pluginsProcessor())
{
    ui->setupUi(this);
    ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listView->setItemDelegate(_delegate);
    ui->listView->setModel(DataManager::instance().model());
    ui->listView->installEventFilter(this);
    ui->listView->setAttribute(Qt::WA_Hover);
    ui->splitter->setSizes({100, 200});

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->layout->insertWidget(1, _panel);

    _timer->setInterval(200);

#ifdef Q_OS_WIN
    Util::setWindowUnfocusable(this);
#endif

    _config->loadTemplates();
    _processor->reset();

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
    connect(ui->quitButton, &QPushButton::clicked, this, &SelectionPasteWindow::close);
    connect(ui->listView, &DetailView::clicked, this, &SelectionPasteWindow::startCheckClick);
    connect(ui->listView, &DetailView::doubleClicked, this, &SelectionPasteWindow::onDoubleClicked);
    connect(_timer, &QTimer::timeout, this, &SelectionPasteWindow::onSingleClicked);
    connect(_panel, qOverload<QPair<int, QString>>(&TemplatePanel::stateAndTemplateChanged), this, qOverload<QPair<int, QString>>(&SelectionPasteWindow::updatePreviewText));
}

void SelectionPasteWindow::updatePreviewText()
{
    updatePreviewText(_panel->getInfo());
}

QString SelectionPasteWindow::applyTemplate(const QString &data, QPair<int, QString> info)
{
    QString resultStr;
    auto [state, templateName] = info;
    if (state) {
        auto templateStr = _config->getTemplate(templateName).first;
        _processor->parse(templateStr);
        resultStr = _processor->yield(data);
    } else {
        resultStr = data;
    }
    return resultStr;
}

bool SelectionPasteWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *e = static_cast<QHoverEvent *>(event);
        auto idx = ui->listView->indexAt(e->position().toPoint());
        if (idx.isValid())
            setCursor(Qt::PointingHandCursor);
        else
            unsetCursor();
    } else if (event->type() == QEvent::Leave) {
        unsetCursor();
    }
    return QMainWindow::eventFilter(watched, event);
}

void SelectionPasteWindow::closeEvent(QCloseEvent *event)
{
    emit reportQuit();
    return QMainWindow::closeEvent(event);
}

void SelectionPasteWindow::run(const QModelIndex &index)
{
    // need to interact with the template system
    auto data = index.data().toString();
    PasteUtil::instance().paste(applyTemplate(data, _panel->getInfo()), true);
}

void SelectionPasteWindow::startCheckClick(const QModelIndex &index)
{
    _timer->start();
    _index = index;
}

void SelectionPasteWindow::onDoubleClicked(const QModelIndex &index[[maybe_unused]])
{
    _timer->stop();
    updatePreviewText();
}

void SelectionPasteWindow::onSingleClicked()
{
    _timer->stop();
    run(_index);
}

void SelectionPasteWindow::updatePreviewText(QPair<int, QString> info)
{
    if (!_index.isValid()) return;
    auto data = _index.data().toString();
    ui->previewBrowser->setText(applyTemplate(data, info));
}

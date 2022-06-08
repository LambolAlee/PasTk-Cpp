#include "selectionpastewindow.h"
#include "ui_selectionpastewindow.h"
#include "util/util.h"
#include "templatepanel.h"
#include "datamanager/itemdelegate.h"
#include "datamanager/datamanager.h"
#include "util/pasteutil.h"

#include <QHoverEvent>
#include <QTimer>


SelectionPasteWindow::SelectionPasteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectionPasteWindow),
    _panel(new TemplatePanel(false, this)),
    _delegate(new ItemDelegate(this, true)),
    _timer(new QTimer(this))
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
    PasteUtil::instance().paste(index.data().toString(), true);
}

void SelectionPasteWindow::startCheckClick(const QModelIndex &index)
{
    _timer->start();
    _index = index;
}

void SelectionPasteWindow::onDoubleClicked(const QModelIndex &index)
{
    _timer->stop();
    ui->previewBrowser->setText(index.data().toString());
}

void SelectionPasteWindow::onSingleClicked()
{
    _timer->stop();
    run(_index);
}

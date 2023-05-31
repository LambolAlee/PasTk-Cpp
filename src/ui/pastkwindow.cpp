#include "pastkwindow.h"
#include "ui_pastkwindow.h"
#include <QToolButton>
#include <QLabel>

//#include "src/paste/pasteutil.h"
#include "src/utils/windowhelper.h"
#include "bottombar.h"
#include "src/settings/config.h"
#include <QActionGroup>

PasTkWindow::PasTkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasTkWindow)
    , m_pin(QIcon(":/pin.png"))
    , m_unpin(QIcon(":/unpin.png"))
    , m_unfocus(false)
{
    ui->setupUi(this);

    initModeActions();
    buildBottomBar();

    m_topmost = false;
    ui->actionAbout_Qt->setIcon(qApp->style()->standardIcon(QStyle::SP_TitleBarMenuButton)); // qtlogo
    connectSignalsWithSlots();
}

PasTkWindow::~PasTkWindow()
{
    delete ui;
    delete m_bottombar;
    delete m_mode_actions;
}

const QList<QAction *> PasTkWindow::bottomBarActions()
{
    return m_bottombar->actions();
}

QAction *PasTkWindow::preferencesAction()
{
    return ui->actionSettings;
}

bool PasTkWindow::topmost() const
{
    return m_topmost;
}

void PasTkWindow::setTopmost(bool value)
{
    m_topmost = value;
}

bool PasTkWindow::unfocus() const
{
    return m_unfocus;
}

void PasTkWindow::setUnfocus(bool value)
{
    m_unfocus = value;
}

void PasTkWindow::showDetailContent()
{
    static bool flag = true;
//    ui->stackedWidget->setCurrentIndex(1);
    WindowHelper::setWindowUnfocusable(this, flag);
    flag = !flag;
//    PasteUtil::instance().paste(this);
}

void PasTkWindow::connectSignalsWithSlots()
{
    connect(ui->startButton, &QPushButton::clicked, this, &PasTkWindow::showDetailContent);
    connect(ui->actionTopmost, &QAction::toggled, this, [this](bool checked){
        WindowHelper::setTopmost(this, checked);
        if (checked)
            ui->actionTopmost->setIcon(m_pin);
        else
            ui->actionTopmost->setIcon(m_unpin);
    });
}

void PasTkWindow::initModeActions()
{
    int checkedMode = Config().getLastUsedMode();
    qDebug() << checkedMode;
    int mode = 0;
    m_mode_actions = new QActionGroup(this);
    m_mode_actions->setExclusive(true);
    for (auto &&action: {ui->actionContinuous_Mode, ui->actionSelection_Mode}) {
        action->setData(mode);
        if (mode++ == checkedMode)
            action->setChecked(true);
        m_mode_actions->addAction(action);
    }
}

void PasTkWindow::buildBottomBar()
{
    m_bottombar = new BottomBar(this);
    ui->centralwidget->layout()->addWidget(m_bottombar);
    m_bottombar->setModeActions(m_mode_actions);
}

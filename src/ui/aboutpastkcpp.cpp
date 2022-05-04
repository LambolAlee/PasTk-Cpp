#include "aboutpastkcpp.h"
#include "ui_aboutpastkcpp.h"

#include "version.h"

#include <QDesktopServices>

AboutPasTkCpp::AboutPasTkCpp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutPasTkCpp)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(680, 480);
    ui->versionLabel->setText(version);

    connectSignalsWithSlots();
}

AboutPasTkCpp::~AboutPasTkCpp()
{
    delete ui;
}

void AboutPasTkCpp::connectSignalsWithSlots()
{
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AboutPasTkCpp::accept);
    connect(ui->codeJumper, &QToolButton::clicked, this, &AboutPasTkCpp::jump2ProjectHomePage);
}

void AboutPasTkCpp::jump2ProjectHomePage()
{
    QUrl url("https://github.com/LambolAlee/PasTk-Cpp");
    QDesktopServices::openUrl(url);
}

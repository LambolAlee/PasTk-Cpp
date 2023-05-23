#include "pluginbrowserdialog.h"
#include "ui_pluginbrowserdialog.h"
#include "formatter/pluginmanager.h"
#include "plugindetaildialog.h"

#include <QSortFilterProxyModel>
#include <QStandardItemModel>


bool PluginBrowserDialog::_modified = false;

PluginBrowserDialog::PluginBrowserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginBrowserDialog)
{
    ui->setupUi(this);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QStandardItemModel *sourceModel = PluginManager::instance().model();
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(sourceModel);
    ui->treeView->setModel(_proxyModel);

    ui->restartLabel->setVisible(modified());
    ui->detailButton->setEnabled(false);

    connectSignalsWithSlots();
    resize(520, 320);
}

PluginBrowserDialog::~PluginBrowserDialog()
{
    delete ui;
}

void PluginBrowserDialog::setModified(bool state)
{
    _modified = state;
}

bool PluginBrowserDialog::modified()
{
    return _modified;
}

void PluginBrowserDialog::checkCheckedItem(QStandardItem *item)
{
    if (!item) return;
    if (item->isCheckable()) {
        PluginManager::instance().setEnabled(item->data().toString(), item->checkState()==Qt::Checked);
        setModified(true);
        ui->restartLabel->show();
    }
}

void PluginBrowserDialog::openDetailWindow(const QModelIndex &index)
{
    QString path;
    if (!index.isValid()) return;
    if (index.column() != 1)
        path = index.siblingAtColumn(1).data(Qt::UserRole +1).toString();
    else
        path = index.data(Qt::UserRole +1).toString();
    auto info = PluginManager::instance().getInfoOf(path);

    PluginDetailDialog dialog(info, this);
    dialog.exec();
}

void PluginBrowserDialog::openDetailWindow()
{
    openDetailWindow(ui->treeView->currentIndex());
}

void PluginBrowserDialog::connectSignalsWithSlots()
{
    connect(ui->treeView, &QTreeView::clicked, this, [=](const QModelIndex &index){if (index.isValid()) ui->detailButton->setEnabled(true);});
    connect(ui->detailButton, &QPushButton::clicked, this, qOverload<>(&PluginBrowserDialog::openDetailWindow));
    connect(ui->treeView, &QTreeView::activated, this, qOverload<const QModelIndex &>(&PluginBrowserDialog::openDetailWindow));
    connect(PluginManager::instance().model(), &QStandardItemModel::itemChanged, this, &PluginBrowserDialog::checkCheckedItem);
}

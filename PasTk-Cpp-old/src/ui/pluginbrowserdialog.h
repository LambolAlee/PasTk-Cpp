#ifndef PLUGINBROWSERDIALOG_H
#define PLUGINBROWSERDIALOG_H

#include <QDialog>

namespace Ui {
class PluginBrowserDialog;
}

class QSortFilterProxyModel;
class QStandardItem;

class PluginBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginBrowserDialog(QWidget *parent = nullptr);
    ~PluginBrowserDialog();

    static void setModified(bool state);
    static bool modified();

private slots:
    void checkCheckedItem(QStandardItem *item);
    void openDetailWindow(const QModelIndex &index);
    void openDetailWindow();

private:
    void connectSignalsWithSlots();

private:
    Ui::PluginBrowserDialog *ui;
    QSortFilterProxyModel *_proxyModel;
    static bool _modified;
};

#endif // PLUGINBROWSERDIALOG_H

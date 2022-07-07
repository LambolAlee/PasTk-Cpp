#ifndef PLUGINDETAILDIALOG_H
#define PLUGINDETAILDIALOG_H

#include <QDialog>

namespace Ui {
class PluginDetailDialog;
}

struct PluginInfo;

class PluginDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDetailDialog(PluginInfo info, QWidget *parent = nullptr);
    ~PluginDetailDialog();

private:
    Ui::PluginDetailDialog *ui;
};

#endif // PLUGINDETAILDIALOG_H

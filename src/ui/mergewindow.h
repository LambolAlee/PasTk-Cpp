#ifndef MERGEWINDOW_H
#define MERGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class MergeWindow;
}

class TemplatePanel;
class Config;
class Processor;

class MergeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MergeWindow(QWidget *parent = nullptr);
    ~MergeWindow();

signals:
    void reportQuit();

private slots:
    //void updatePreviewText(const QString &mergeStr, QPair<int, QString> info);
    void run();

private:
    Ui::MergeWindow *ui;
    TemplatePanel *_panel;
    Config *_config;
    Processor *_processor;

    void connectSignalsWithSlots();

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MERGEWINDOW_H

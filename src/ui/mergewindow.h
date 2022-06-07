#ifndef MERGEWINDOW_H
#define MERGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class MergeWindow;
}

class TemplatePanel;

class MergeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MergeWindow(QWidget *parent = nullptr);
    ~MergeWindow();

signals:
    void reportQuit();

private:
    Ui::MergeWindow *ui;
    TemplatePanel *_panel;

    void connectSignalsWithSlots();

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MERGEWINDOW_H

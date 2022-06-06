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

private:
    Ui::MergeWindow *ui;
    TemplatePanel *_panel;

    void connectSignalsWithSlots();
};

#endif // MERGEWINDOW_H

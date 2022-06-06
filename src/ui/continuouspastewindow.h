#ifndef CONTINUOUSPASTEWINDOW_H
#define CONTINUOUSPASTEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ContinuousPasteWindow;
}

class DataManager;
class TemplatePanel;

class ContinuousPasteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContinuousPasteWindow(QWidget *parent = nullptr);
    ~ContinuousPasteWindow();

private:
    Ui::ContinuousPasteWindow *ui;
    DataManager &_dataManager;
    TemplatePanel *_panel;
    int _current;

    void connectSignalsWithSlots();
};

#endif // CONTINUOUSPASTEWINDOW_H

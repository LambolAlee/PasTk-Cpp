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

signals:
    void reportQuit();

private:
    Ui::ContinuousPasteWindow *ui;
    DataManager &_dataManager;
    TemplatePanel *_panel;
    int _current;

    void connectSignalsWithSlots();

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // CONTINUOUSPASTEWINDOW_H

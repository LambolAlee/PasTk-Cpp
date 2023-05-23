#ifndef CONTINUOUSPASTEWINDOW_H
#define CONTINUOUSPASTEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ContinuousPasteWindow;
}

class DataManager;
class TemplatePanel;
class Processor;
class Config;

class ContinuousPasteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContinuousPasteWindow(QWidget *parent = nullptr);
    ~ContinuousPasteWindow();

signals:
    void reportQuit();

private slots:
    void run();
    void prepareNextData();
    void updatePreviewText(QPair<int, QString> info);

private:
    Ui::ContinuousPasteWindow *ui;
    DataManager &_dataManager;
    Config *_config;
    TemplatePanel *_panel;
    Processor *_processor;
    int _current;
    QString _currentData;
    int _max;
    bool _endToQuit;

    void connectSignalsWithSlots();
    bool checkForTheEnd();
    void updatePreviewText();

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // CONTINUOUSPASTEWINDOW_H

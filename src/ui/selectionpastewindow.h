#ifndef SELECTIONPASTEWINDOW_H
#define SELECTIONPASTEWINDOW_H

#include <QMainWindow>

namespace Ui {
class SelectionPasteWindow;
}

class TemplatePanel;
class ItemDelegate;

class SelectionPasteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionPasteWindow(QWidget *parent = nullptr);
    ~SelectionPasteWindow();

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void reportQuit();

private:
    Ui::SelectionPasteWindow *ui;
    TemplatePanel *_panel;
    ItemDelegate *_delegate;

    void connectSignalsWithSlots();   

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SELECTIONPASTEWINDOW_H

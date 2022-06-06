#ifndef SELECTIONPASTEWINDOW_H
#define SELECTIONPASTEWINDOW_H

#include <QMainWindow>

namespace Ui {
class SelectionPasteWindow;
}

class TemplatePanel;

class SelectionPasteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionPasteWindow(QWidget *parent = nullptr);
    ~SelectionPasteWindow();

private:
    Ui::SelectionPasteWindow *ui;
    TemplatePanel *_panel;

    void connectSignalsWithSlots();
};

#endif // SELECTIONPASTEWINDOW_H

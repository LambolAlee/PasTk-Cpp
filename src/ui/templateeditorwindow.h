#ifndef TEMPLATEEDITORWINDOW_H
#define TEMPLATEEDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
class TemplateEditorWindow;
}

class TemplateEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplateEditorWindow(QWidget *parent = nullptr);
    ~TemplateEditorWindow();

private:
    Ui::TemplateEditorWindow *ui;
};

#endif // TEMPLATEEDITORWINDOW_H

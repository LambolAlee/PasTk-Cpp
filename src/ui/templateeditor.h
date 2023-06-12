#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QMainWindow>

namespace Ui {
class TemplateEditor;
}

class TemplateEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplateEditor(QWidget *parent = nullptr);
    ~TemplateEditor();

private:
    Ui::TemplateEditor *ui;
};

#endif // TEMPLATEEDITOR_H

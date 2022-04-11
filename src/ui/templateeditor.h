#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QWidget>

namespace Ui {
class TemplateEditor;
}

class TemplateEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateEditor(QWidget *parent = nullptr);
    ~TemplateEditor();

private:
    Ui::TemplateEditor *ui;
};

#endif // TEMPLATEEDITOR_H

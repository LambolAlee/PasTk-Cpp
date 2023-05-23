#include "templateeditorwindow.h"
#include "ui_templateeditorwindow.h"

TemplateEditorWindow::TemplateEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplateEditorWindow)
{
    ui->setupUi(this);
}

TemplateEditorWindow::~TemplateEditorWindow()
{
    delete ui;
}

#include "templateeditorwindow.h"
#include "ui_templateeditorwindow.h"

TemplateEditorWindow::TemplateEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplateEditorWindow)
{
    ui->setupUi(this);
    ui->toolBar->setOrientation(Qt::Vertical);
    ui->toolBar->setFloatable(false);
    ui->toolBar->setMovable(false);
}

TemplateEditorWindow::~TemplateEditorWindow()
{
    delete ui;
}

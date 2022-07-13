#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QStandardItemModel>
#include <QMainWindow>


namespace Ui {
class TemplateEditor;
}

class TemplateInfoWidget;
class TemplateSelectorPanel;
class QPluginLoader;
class QToolButton;

class TemplateEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplateEditor(QWidget *parent = nullptr);
    ~TemplateEditor();

private:
    void initHelpDock();
    void loadPluginHelp(QPluginLoader *loader);
    void connectSignalsWithSlots();

private slots:
    void showHelp(const QModelIndex &index);
    void addTag(const QModelIndex &index);
    void toggleTagDock(bool state);

private:
    Ui::TemplateEditor *ui;
    TemplateInfoWidget *_infoWidget;
    TemplateSelectorPanel *_selectorPanel;
    QStandardItemModel _model;
    QToolButton *_tagDockBtn;
};

#endif // TEMPLATEEDITOR_H

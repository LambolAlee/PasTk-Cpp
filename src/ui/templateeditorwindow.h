#ifndef TEMPLATEEDITORWINDOW_H
#define TEMPLATEEDITORWINDOW_H

#include <QMainWindow>
#include "src/settings/config.h"

namespace Ui {
class TemplateEditorWindow;
}

class TemplateEditorPanel;
class TagsDrawerContent;
class QListWidgetItem;

class TemplateEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplateEditorWindow(QWidget *parent = nullptr);
    ~TemplateEditorWindow();

    void showWindow(bool with_apply);

signals:
    void templateSelected(bool changed, const QString &templateName);

private:
    void initTemplateListContent();
    void connectSignalsWithSlots();

private slots:
    void deleteTemplate(bool refresh_default);
    void modifyTemplate(const TemplatePair &pair);
    void selectItem(QListWidgetItem *current);
    void addNewTemplate(const TemplatePair &pair);
    void changeDefaultTemplate(const QString &current, const QString &previous);
    void deliverTemplate(bool changed);

private:
    Ui::TemplateEditorWindow *ui;
    TemplateEditorPanel *m_panel;
    TagsDrawerContent *m_content;
    Config m_config;
    QListWidgetItem *m_previous;
};

#endif // TEMPLATEEDITORWINDOW_H

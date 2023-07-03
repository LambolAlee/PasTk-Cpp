#ifndef TEMPLATEEDITORPANEL_H
#define TEMPLATEEDITORPANEL_H

#include <QMainWindow>
#include "src/settings/config.h"

namespace Ui {
class TemplateEditorPanel;
}

class TemplateEditorPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplateEditorPanel(QWidget *parent = nullptr);
    ~TemplateEditorPanel();

    void selectTemplate(const TemplatePair &templatePair, bool favor);
    void selectTemplate(const QString &templateName, bool favor);
    void showApplyButton(bool with_apply);

public slots:
    void pasteSelectedTag(const QString &tag);

private:
    void initPanelContent();
    bool submit();
    void restore();
    void connectSignalsWithSlots();
    void setFavorState(bool favor);
    void fillWithTemplatePair(const TemplatePair &templatePair, bool favor);

private slots:
    void toggleFavoriteState();

signals:
    void toggleTagDrawer(bool);
    void templateModified(const TemplatePair &);
    void newTemplateCreated(const TemplatePair &);
    void defaultTemplateChanged(const QString &current, const QString &previous);
    void removeActionTriggered(const QString &);
    void deleteActionTriggered(bool refresh_default);
    void templateSelected(bool changed);

private:
    Ui::TemplateEditorPanel *ui;
    Config m_config;
    QPair<TemplatePair, bool> m_current_template;   // TemplatePair, favor
    bool m_addition;
    QIcon m_star_blank;
    QIcon m_star;
};

#endif // TEMPLATEEDITORPANEL_H

#ifndef CONTINUOUSPASTEWIDGET_H
#define CONTINUOUSPASTEWIDGET_H

#include <QWidget>

namespace Ui {
class ContinuousPasteWidget;
}

class DataManager;
class TemplateManager;
class Segments;
class PasteUtil;

class ContinuousPasteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContinuousPasteWidget(QWidget *parent = nullptr);
    ~ContinuousPasteWidget();

public:
    void prepare(bool use_template);
    void selectTemplate(bool changed, const QString &templateName, const QString &templateStr);
    void renderText(bool use_template);

signals:
    void pasteFinished();

private:
    void renderText();
    void connectSignalsWithSlots();

private slots:
    void paste();
    void skip();

private:
    Ui::ContinuousPasteWidget *ui;
    DataManager *m_datamanager;
    TemplateManager *m_template_manager;
    Segments *m_seg;
    PasteUtil *m_paste;
    bool m_use_template;
};

#endif // CONTINUOUSPASTEWIDGET_H

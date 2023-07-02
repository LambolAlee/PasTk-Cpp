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
    void prepare();

signals:
    void backToHome();
    void pasteFinished();

private:
    void connectSignalsWithSlots();

private slots:
    void renderText();
    void paste();
    void skip();

private:
    Ui::ContinuousPasteWidget *ui;
    DataManager *m_datamanager;
    TemplateManager *m_template_manager;
    Segments *m_seg;
    PasteUtil *m_paste;
    QString m_current_template;
};

#endif // CONTINUOUSPASTEWIDGET_H

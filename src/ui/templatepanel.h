#ifndef TEMPLATEPANEL_H
#define TEMPLATEPANEL_H

#include <QWidget>

namespace Ui {
class TemplatePanel;
}

class TemplatePanel : public QWidget
{
    Q_OBJECT

public:
    explicit TemplatePanel(QWidget *parent = nullptr);
    explicit TemplatePanel(bool mergeOption = false, QWidget *parent = nullptr);
    ~TemplatePanel();

private:
    Ui::TemplatePanel *ui;

    void connectSignalsWithSlots();
};

#endif // TEMPLATEPANEL_H

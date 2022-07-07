#ifndef TEMPLATESELECTORPANEL_H
#define TEMPLATESELECTORPANEL_H

#include <QWidget>

namespace Ui {
class TemplateSelectorPanel;
}

class TemplateSelectorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateSelectorPanel(QWidget *parent = nullptr);
    ~TemplateSelectorPanel();

private:
    Ui::TemplateSelectorPanel *ui;
};

#endif // TEMPLATESELECTORPANEL_H

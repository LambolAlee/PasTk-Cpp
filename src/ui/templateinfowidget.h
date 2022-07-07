#ifndef TEMPLATEINFOWIDGET_H
#define TEMPLATEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class TemplateInfoWidget;
}

class TemplateInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateInfoWidget(QWidget *parent = nullptr);
    ~TemplateInfoWidget();

private:
    Ui::TemplateInfoWidget *ui;
};

#endif // TEMPLATEINFOWIDGET_H

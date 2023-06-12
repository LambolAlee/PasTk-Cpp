#ifndef PASTEPANEL_H
#define PASTEPANEL_H

#include <QWidget>

namespace Ui {
class PastePanel;
}

class PastePanel : public QWidget
{
    Q_OBJECT

public:
    explicit PastePanel(QWidget *parent = nullptr);
    ~PastePanel();

private:
    Ui::PastePanel *ui;
};

#endif // PASTEPANEL_H

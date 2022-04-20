#ifndef ITEMFLOATBUTTONS_H
#define ITEMFLOATBUTTONS_H

#include <QWidget>

namespace Ui {
class ItemFloatButtons;
}

class ItemFloatButtons : public QWidget
{
    Q_OBJECT

public:
    explicit ItemFloatButtons(QWidget *parent = nullptr);
    ~ItemFloatButtons();

private:
    Ui::ItemFloatButtons *ui;
};

#endif // ITEMFLOATBUTTONS_H

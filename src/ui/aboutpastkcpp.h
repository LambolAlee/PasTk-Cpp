#ifndef ABOUTPASTKCPP_H
#define ABOUTPASTKCPP_H

#include <QDialog>

namespace Ui {
class AboutPasTkCpp;
}

class AboutPasTkCpp : public QDialog
{
    Q_OBJECT

public:
    explicit AboutPasTkCpp(QWidget *parent = nullptr);
    ~AboutPasTkCpp();

private:
    Ui::AboutPasTkCpp *ui;

    void connectSignalsWithSlots();
    void jump2ProjectHomePage();
};

#endif // ABOUTPASTKCPP_H

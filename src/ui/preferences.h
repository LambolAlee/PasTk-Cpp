#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr);
    ~Preferences();

private slots:
    void save();
    void resetGeneralSettings();
    void resetHotkeySettings();

private:
    Ui::Preferences *ui;

    void connectSignalsWithSlots();
};

#endif // PREFERENCES_H

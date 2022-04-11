#ifndef DETAILEDITOR_H
#define DETAILEDITOR_H

#include <QMainWindow>

namespace Ui {
class DetailEditor;
}

class DetailEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetailEditor(QWidget *parent = nullptr);
    ~DetailEditor();

private:
    Ui::DetailEditor *ui;
};

#endif // DETAILEDITOR_H

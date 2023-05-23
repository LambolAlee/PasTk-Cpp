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

    QPair<int, QString> getInfo();
    QString getMergeStr();

signals:
    void stateAndTemplateChanged(QPair<int, QString>);
    void stateAndTemplateChanged(const QString &mergeStr, QPair<int, QString>);

private slots:
    void emitStateAndTemplateChangedSig();

private:
    Ui::TemplatePanel *ui;
    QString _mergeChar;

    void connectSignalsWithSlots();
    bool isTemplateEnabled();
    void listTemplates();
};

#endif // TEMPLATEPANEL_H

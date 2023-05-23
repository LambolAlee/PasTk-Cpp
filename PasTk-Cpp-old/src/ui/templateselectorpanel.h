#ifndef TEMPLATESELECTORPANEL_H
#define TEMPLATESELECTORPANEL_H

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class TemplateSelectorPanel;
}

class Config;

class TemplateSelectorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateSelectorPanel(QWidget *parent = nullptr);
    ~TemplateSelectorPanel();

signals:
    void click(const QModelIndex &);
    void newTemplate();
    void clearInfo(const QString &name);

public slots:
    void onNewItemSaved(const QString &name);
    void rename(const QString &oldName, const QString &newName);
    void setDefaultTemplate();

private slots:
    void createNewTemplate();
    void deleteTemplate();
    void unsetDefaultTemplate();

private:
    void initTemplateList();
    void connectSignalsWithSlots();
    void highlightDefault(QStandardItem *item, bool state);
    void highlightDefault(const QModelIndex &index, bool state);

private:
    Ui::TemplateSelectorPanel *ui;
    QStandardItemModel _model;
    QStandardItem *_temp = nullptr;
    Config *_config;

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TEMPLATESELECTORPANEL_H

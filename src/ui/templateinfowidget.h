#ifndef TEMPLATEINFOWIDGET_H
#define TEMPLATEINFOWIDGET_H

#include <QWidget>


namespace Ui {
class TemplateInfoWidget;
}

class QAbstractButton;
class Config;

class TemplateInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateInfoWidget(QWidget *parent = nullptr);
    ~TemplateInfoWidget();

    void addTag(const QString &tag);
    void saveConfig();

signals:
    void newItemSaved(const QString &name);
    void defaultTemplateSet();
    void itemRenamed(const QString &oldName, const QString &newName);

public slots:
    void showTemplate(const QModelIndex &index);
    void initForNewTemplate();
    void deleteItem(const QString &name);

private slots:
    void save();
    void reset();
    void setDefaultTemplate();
    void applyTemplate();

private:
    void fillPage();
    void connectSignalsWithSlots();
    void clearAll();

private:
    Ui::TemplateInfoWidget *ui;
    bool _editNewItem;
    bool _modified;
    QString _currentEditedName;
    Config *_config;
};

#endif // TEMPLATEINFOWIDGET_H

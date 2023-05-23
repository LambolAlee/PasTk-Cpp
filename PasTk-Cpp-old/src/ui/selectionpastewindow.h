#ifndef SELECTIONPASTEWINDOW_H
#define SELECTIONPASTEWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
class SelectionPasteWindow;
}

class TemplatePanel;
class ItemDelegate;
class Config;
class Processor;

class SelectionPasteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionPasteWindow(QWidget *parent = nullptr);
    ~SelectionPasteWindow();

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void reportQuit();

private slots:
    void run(const QModelIndex &index);
    void startCheckClick(const QModelIndex &index);
    void onDoubleClicked(const QModelIndex &index);
    void onSingleClicked();
    void updatePreviewText(QPair<int, QString> info);

private:
    Ui::SelectionPasteWindow *ui;
    TemplatePanel *_panel;
    ItemDelegate *_delegate;
    QTimer *_timer;
    QModelIndex _index;
    Config *_config;
    Processor *_processor;

    void connectSignalsWithSlots();
    void updatePreviewText();
    QString applyTemplate(const QString &data, QPair<int, QString> info);

// QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SELECTIONPASTEWINDOW_H

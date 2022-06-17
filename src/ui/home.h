#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

#include "util/clipboardlistner.h"
#include "pastemanager.h"

class BottomBar;
class ItemDelegate;
class QAbstractItemModel;
class ItemEditorDialog;
class QActionGroup;

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

    const QList<QAction *> bottomBarActions();
    QAction *preferencesAction();

signals:
    void altKeyTriggered();

private slots:
    void toggleMenubar();
    void toggleMenubar(bool state);

    void editOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void pasteOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void deleteOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void setData(const QModelIndex &index, const QString &data);
    void clearSelectedItems();

    void switchCopy(bool state);
    void showHelpContent();
    void showAboutMe();

    void startPaste();
    void openSettingsWindow();
    void updateUi();

private:
    Ui::Home *ui;
    BottomBar *_bottomBar;
    ItemDelegate *_delegate;
    ItemEditorDialog *_editor;
    ClipBoardListner _listener;
    QActionGroup *_modeActions;

    PasteManager _manager;

    void connectSignalsWithSlots();
    void showDetailContent();
    void initModeActions();

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
};
#endif // HOME_H

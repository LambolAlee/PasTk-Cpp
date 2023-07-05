#ifndef PASTKWINDOW_H
#define PASTKWINDOW_H

#include <QMainWindow>
#include "src/settings/config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PasTkWindow; }
QT_END_NAMESPACE

class BottomBar;
class DataManager;
class ItemEditorDialog;
class TemplateEditorWindow;
class ContinuousPasteWidget;
class Preferences;
class SelectionPasteWidget;
class TemplateManager;

enum ContextIndex {
    Start,
    Detail,
    Paste,
};

class PasTkWindow : public QMainWindow
{
    Q_OBJECT

public:
    PasTkWindow(QWidget *parent = nullptr);
    ~PasTkWindow();

    const QList<QAction *> bottomBarActions();
    QAction *preferencesAction();
    const QMenu *toolMenu();
    const QMenu *helpMenu();

signals:
    void topmostChanged(bool current);

private slots:
    void showAboutMe();
    void handleSwitchCopy(bool on);
    void clearSelectedItems();
    void addNewItem(const QString &text, bool before);
    void editSelectedItem();
    void backToHome();

private:
    void connectSignalsWithSlots();
    void initModeActions();
    void buildBottomBar();
    void resetWindowState();
    void startPaste();
    void switchToPage(ContextIndex index, int mode=0);
    void setWindowUnfocusable(bool unfocus);

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::PasTkWindow *ui;
    BottomBar *m_bottombar;
    QActionGroup *m_mode_actions;
    DataManager *m_datamanager;
    ContextIndex m_current_page;
    ItemEditorDialog *m_editor;
    TemplateEditorWindow *m_editor_window;
    ContinuousPasteWidget *m_continuous;
    SelectionPasteWidget *m_selection;
    Preferences *m_preferences;
    Config m_config;
    TemplateManager *m_template_manager;

    QIcon m_pin;
    QIcon m_unpin;

    bool m_topmost;
    bool m_unfocus;
};
#endif // PASTKWINDOW_H

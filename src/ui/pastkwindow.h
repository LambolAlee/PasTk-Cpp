#ifndef PASTKWINDOW_H
#define PASTKWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class PasTkWindow; }
QT_END_NAMESPACE

class BottomBar;
class DataManager;
class ItemEditorDialog;
class TemplateEditorWindow;
class ContinuousPasteWidget;

enum ContextIndex {
    Start,
    Detail,
    Paste,
};

class PasTkWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(bool topmost READ topmost WRITE setTopmost NOTIFY topmostChanged)
    Q_PROPERTY(bool unfocus READ unfocus WRITE setUnfocus)

public:
    PasTkWindow(QWidget *parent = nullptr);
    ~PasTkWindow();

    const QList<QAction *> bottomBarActions();
    QAction *preferencesAction();
    const QMenu *toolMenu();
    const QMenu *helpMenu();

signals:
    void topmostChanged(bool current);

public:
    bool topmost() const;
    void setTopmost(bool value);

    bool unfocus() const;
    void setUnfocus(bool value);

private slots:
    void showAboutMe();
    void switchCopy(bool on);
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

    QIcon m_pin;
    QIcon m_unpin;

    bool m_topmost;
    bool m_unfocus;
};
#endif // PASTKWINDOW_H

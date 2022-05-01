#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

#include "util/clipboardlistner.h"

class BottomBar;
class ItemDelegate;
class QAbstractItemModel;
class ItemEditorDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void toggleMenubar();

    void editOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void pasteOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void deleteOne(const QModelIndex &index, QAbstractItemModel *model = nullptr);
    void setData(const QModelIndex &index, const QString &data);

    void switchCopy(bool state);
    void showHelpContent();

private:
    Ui::Home *ui;
    BottomBar *_bottomBar;
    ItemDelegate *_delegate;
    ItemEditorDialog *_editor;
    ClipBoardListner _listner;

    void connectSignalsWithSlots();
    void initDetailView();
    void showDetailContent();
};
#endif // HOME_H

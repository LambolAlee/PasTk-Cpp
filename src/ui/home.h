#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

class BottomBar;
class ItemDelegate;
class QAbstractItemModel;

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
    void triggerAboutQtAction();
    void editOne(QAbstractItemModel *model, const QModelIndex &index);

private:
    Ui::Home *ui;
    BottomBar *_bottomBar;
    ItemDelegate *_delegate;

    void connectSignalsWithSlots();
    void initDetailView();
};
#endif // HOME_H

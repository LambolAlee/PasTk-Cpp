#ifndef CLIPBOARDLISTNER_H
#define CLIPBOARDLISTNER_H

#include <QClipboard>
#include <QApplication>


class ClipBoardListner : public QObject
{
    Q_OBJECT
public:
    void start();
    void stop();

    bool isCopying();
    void startQuickPaste();
    void endQuickPaste();

signals:
    void updateCount();

private slots:
    void push();

private:
    bool _inCopying = false;

    QClipboard *_clipboard = qApp->clipboard();
};

#endif // CLIPBOARDLISTNER_H

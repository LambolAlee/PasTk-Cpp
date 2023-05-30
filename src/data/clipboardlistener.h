#ifndef CLIPBOARDLISTENER_H
#define CLIPBOARDLISTENER_H

#include <QObject>

class QClipboard;

class ClipboardListener : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardListener(QObject *parent = nullptr);

    void listen();
    void stop();

signals:
    void newDataOccurred(const QString &);

private:
    QClipboard *m_clip;
};

#endif // CLIPBOARDLISTENER_H

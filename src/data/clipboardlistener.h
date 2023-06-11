#ifndef CLIPBOARDLISTENER_H
#define CLIPBOARDLISTENER_H

#include <QObject>

class QClipboard;
class QTimer;

class ClipboardListener : public QObject
{
    Q_OBJECT

public:
    explicit ClipboardListener(QObject *parent = nullptr);
    ~ClipboardListener();

    void listen();
    void stop();

signals:
    void newDataOccurred(const QString &);

private:
    QClipboard *m_clip;

#ifdef Q_OS_MAC
    QTimer *m_timer;
    QString m_previous_string;
    void checkNewCliipboardText();
#endif
};

#endif // CLIPBOARDLISTENER_H

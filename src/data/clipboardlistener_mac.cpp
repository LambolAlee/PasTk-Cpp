#include "clipboardlistener.h"
#include <QApplication>
#include <QClipboard>
#include <QTimer>


ClipboardListener::ClipboardListener(QObject *parent)
    : QObject{parent}
{
    int delay = 800;
    m_clip = qApp->clipboard();
    m_timer = new QTimer(this);
    m_timer->setInterval(delay);
    connect(m_timer, &QTimer::timeout, this, &ClipboardListener::checkNewCliipboardText);
}

ClipboardListener::~ClipboardListener()
{
    m_clip = nullptr;
    m_timer->stop();
    delete m_timer;
    m_timer = nullptr;
}

void ClipboardListener::listen()
{
    m_previous_string = m_clip->text();
    m_timer->start();
}

void ClipboardListener::stop()
{
    m_timer->stop();
}

void ClipboardListener::checkNewCliipboardText()
{
    QString text = m_clip->text();
    if (!text.isEmpty() && text != m_previous_string) {
        m_previous_string = text;
        emit newDataOccurred(m_previous_string);
    }
}

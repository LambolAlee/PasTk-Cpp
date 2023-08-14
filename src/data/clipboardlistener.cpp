#include "clipboardlistener.h"
#include <QApplication>
#include <QClipboard>


ClipboardListener::ClipboardListener(QObject *parent)
    : QObject{parent}
{
    m_clip = qApp->clipboard();
    connect(m_clip, &QClipboard::dataChanged, this, [this]{
        if (!m_clip->text().isEmpty())
            emit newDataOccurred(m_clip->text());
    });
    stop();
}

ClipboardListener::~ClipboardListener()
{
    m_clip = nullptr;
}

void ClipboardListener::listen()
{
    m_clip->blockSignals(false);
}

void ClipboardListener::stop()
{
    m_clip->blockSignals(true);
}

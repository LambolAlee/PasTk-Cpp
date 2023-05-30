#include "clipboardlistener.h"
#include <QApplication>
#include <QClipboard>

ClipboardListener::ClipboardListener(QObject *parent)
    : QObject{parent}
{
    m_clip = qApp->clipboard();
    connect(m_clip, &QClipboard::dataChanged, this, [this]{
        emit newDataOccurred(m_clip->text());
    });
}

void ClipboardListener::listen()
{
    m_clip->blockSignals(false);
}

void ClipboardListener::stop()
{
    m_clip->blockSignals(true);
}

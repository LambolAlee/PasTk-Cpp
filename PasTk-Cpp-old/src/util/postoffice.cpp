#include "postoffice.h"

#include <QDebug>


PostOffice::PostOffice() {}
PostOffice::~PostOffice() {}

void PostOffice::upload(QObject *obj, const QString &theme, const char *signal, const char *signal_name)
{
    if (_themes.contains(theme) && _themes.value(theme) == obj && _signals.value(theme).first == signal) return;
    _themes.insert(theme, obj);
    _signals.insert(theme, {signal, signal_name});
    QObject::connect(obj, &QObject::destroyed, this, &PostOffice::expire);
}

void PostOffice::remove(const QString &theme)
{
    if (!_themes.contains(theme)) return;
    auto *sender = _themes.take(theme);
    auto signal = _signals.take(theme);
    sender->disconnect(signal.first);
}

void PostOffice::expire(QObject *obj)
{
    qDebug() << "[PostOffice] expire the obj `" << obj << "` from themes";
    if (!obj) return;
    auto theme = _themes.key(obj);
    _themes.remove(theme);
    _signals.remove(theme);
}

bool PostOffice::subscribe(QObject *obj, const QString &theme, const char *slot)
{
    if (!_themes.contains(theme)) return false;
    QObject::connect(_themes.value(theme), _signals.value(theme).first, obj, slot);
    return true;
}

bool PostOffice::unsubscribe(QObject *obj, const QString &theme)
{
    if (!_themes.contains(theme)) return false;
    auto *sender = _themes.value(theme);
    auto signal = _signals.value(theme);
    sender->disconnect(signal.first, obj, 0);
    return true;
}

void PostOffice::post(const QString &theme,
                         QGenericArgument val0,
                         QGenericArgument val1,
                         QGenericArgument val2,
                         QGenericArgument val3,
                         QGenericArgument val4,
                         QGenericArgument val5,
                         QGenericArgument val6,
                         QGenericArgument val7,
                         QGenericArgument val8,
                         QGenericArgument val9)
{
    if (!_themes.contains(theme)) return;
    QMetaObject::invokeMethod(_themes.value(theme), _signals.value(theme).second, Qt::AutoConnection,
                              val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
}

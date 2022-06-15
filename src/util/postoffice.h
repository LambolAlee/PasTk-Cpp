#ifndef POSTOFFICE_H
#define POSTOFFICE_H

#include <QMap>
#include <QObject>
#include <QGenericArgument>

#include "Singleton.h"


class PostOffice : public QObject
{
    Q_OBJECT
    SINGLETON(PostOffice)

public:
    void upload(QObject *obj, const QString &theme, const char *signal, const char *signal_name);
    void remove(const QString &theme);

    bool subscribe(QObject *obj, const QString &theme, const char *slot);
    bool unsubscribe(QObject *obj, const QString &theme);

    void publish(const QString &theme,
                 QGenericArgument val0 = QGenericArgument(nullptr),
                 QGenericArgument val1 = QGenericArgument(),
                 QGenericArgument val2 = QGenericArgument(),
                 QGenericArgument val3 = QGenericArgument(),
                 QGenericArgument val4 = QGenericArgument(),
                 QGenericArgument val5 = QGenericArgument(),
                 QGenericArgument val6 = QGenericArgument(),
                 QGenericArgument val7 = QGenericArgument(),
                 QGenericArgument val8 = QGenericArgument(),
                 QGenericArgument val9 = QGenericArgument());

private slots:
    void expire(QObject *obj);

private:
    QMap<QString, QObject *> _themes;
    QMap<QString, QPair<const char *, const char *>> _signals;      // QPair<signal, signal_name>
};

#endif // POSTOFFICE_H

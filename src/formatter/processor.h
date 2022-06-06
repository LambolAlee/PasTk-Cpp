#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QList>
#include <QObject>
#include <QPluginLoader>
#include <QXmlStreamReader>

#include "generatorinterface.h"


class Processor : public QObject
{
    Q_OBJECT
public:
    Processor(QList<QPluginLoader *> loaders);

    void parse(const QString &templateStr);
    QString yield(const QString &data);

private:
    QXmlStreamReader _xml;
    QTextStream _stream;
    QVariantList _res;
    QString _data;
    QList<IGenerator *> _generators;

    IGenerator *begin();
};

#endif // PROCESSOR_H

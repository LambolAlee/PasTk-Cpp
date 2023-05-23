#ifndef PROCESSOR_H
#define PROCESSOR_H

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
    void reset();

private:
    QXmlStreamReader _xml;
    QTextStream _stream;
    QVariantList _res;
    QString _data;
    QList<IGenerator *> _generators;
    QString _currentTemplate;
};

#endif // PROCESSOR_H

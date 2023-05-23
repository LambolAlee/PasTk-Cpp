#ifndef TAGLOADER_H
#define TAGLOADER_H

#include <QXmlStreamReader>
#include <QTextStream>


class TagLoader
{
public:
    void parse(const QString &templateStr);

private:
    QXmlStreamReader m_xml;
    QTextStream m_stream;
};

#endif // TAGLOADER_H


#ifndef TEMPLATEPARSER_H
#define TEMPLATEPARSER_H

#include <QXmlStreamReader>
#include "src/tag/tagloader.h"

class Segments;

class TemplateParser
{
public:
    TemplateParser();
    ~TemplateParser();

    Segments *parse(const QString &templateStr);

private:
    QXmlStreamReader m_xml;
    TagChain *m_chain;
};

#endif // TEMPLATEPARSER_H


#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H

#include "src/utils/Singleton.h"

class Segments;
class TemplateParser;

class TemplateManager
{
    SINGLETON(TemplateManager)

public:
    Segments *loadTemplateSegments(const QString &templateName, const QString &templateStr);
    Segments *getTemplateSegments(const QString &templateName);

private:
    QMap<QString, Segments *> *m_cache;
    TemplateParser *m_parser;
};

#endif // TEMPLATEMANAGER_H


#include "templatemanager.h"
#include "templateparser.h"
#include <QMap>

TemplateManager::TemplateManager()
{
    m_cache = new QMap<QString, Segments *>;
    m_parser = new TemplateParser;
}

TemplateManager::~TemplateManager()
{
    qDeleteAll(*m_cache);
    m_cache->clear();
    m_cache = nullptr;

    delete m_parser;
    m_parser = nullptr;
}

Segments *TemplateManager::loadTemplateSegments(const QString &templateName, const QString &templateStr)
{
    Segments *res = getTemplateSegments(templateName);
    if (res)
        return res;

    res = m_parser->parse(templateStr);
    m_cache->insert(templateName, res);
    return res;
}

Segments *TemplateManager::getTemplateSegments(const QString &templateName)
{
    if (m_cache->contains(templateName))
        return m_cache->value(templateName);
    else
        return nullptr;
}

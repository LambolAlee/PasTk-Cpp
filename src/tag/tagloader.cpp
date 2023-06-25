#include "tagloader.h"
#include "coretag.h"
#include "seqtag.h"


#define loadITag(TagClass) \
tempTag = m_chain; \
m_chain = new TagClass; \
m_tags.insert(m_chain->tags()); \
m_chain->setNext(tempTag); \


TagLoader::TagLoader()
{
    ITag *tempTag;
    m_chain = new SeqTag;
    m_tags.insert(m_chain->tags());

    loadITag(CoreTag)
}

TagLoader::~TagLoader()
{
    delete m_chain;
}

TagChain *TagLoader::chain()
{
    return m_chain;
}

const QMap<QString, QString> &TagLoader::tagDoc() const
{
    return m_tags;
}

#ifndef TAGLOADER_H
#define TAGLOADER_H

#include "ITag.h"
#include "src/utils/Singleton.h"


using TagChain = ITag;

class TagLoader
{
    SINGLETON(TagLoader)

public:
    TagChain *chain();
    const QMap<QString, QString> &tagDoc() const;

private:
    TagChain *m_chain;
    QMap<QString, QString> m_tags;
};

#endif // TAGLOADER_H

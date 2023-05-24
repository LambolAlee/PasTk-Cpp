
#include "coretag.h"
#include <QVariant>


CoreTag::~CoreTag()
{
    m_nextTag = nullptr;
}

QList<QString> CoreTag::tags() const
{
    return QList<QString>({"<data>", "<br>", "<tab>"});
}

QVariant CoreTag::handle(QStringView tagName, const QXmlStreamAttributes &attrs)
{
}

void CoreTag::setNext(ITag *tag)
{
    m_nextTag = tag;
}

ITag *CoreTag::next() const
{
    return m_nextTag;
}

void CoreTag::reset() const
{
}

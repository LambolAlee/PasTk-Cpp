
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

ISegment *CoreTag::handle(QStringView tagName, [[maybe_unused]]const QXmlStreamAttributes &attrs)
{
    CoreSegment *seg = new CoreSegment;
    if (tagName == QStringLiteral("data")) {

    }
    return seg;
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

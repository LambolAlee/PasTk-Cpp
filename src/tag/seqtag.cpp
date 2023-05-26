
#include "seqtag.h"

SeqTag::SeqTag()
{

}



QList<QString> SeqTag::tags() const
{
}

ISegment *SeqTag::handle(QStringView tagName, [[maybe_unused]]const QXmlStreamAttributes &attrs)
{
}

void SeqTag::setNext(ITag *tag)
{
}

ITag *SeqTag::next() const
{
}

void SeqTag::reset() const
{
}

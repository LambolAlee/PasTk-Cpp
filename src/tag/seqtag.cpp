
#include "seqtag.h"
#include <QXmlStreamAttributes>


SeqTag::SeqTag()
{
    m_tags = {"index"};
    m_nextTag = nullptr;
}

SeqTag::~SeqTag()
{
    delete m_nextTag;
    m_nextTag = nullptr;
}

QList<QString> SeqTag::tags() const
{
    return m_tags;
}

ISegment *SeqTag::handle(QStringView tagName, const QXmlStreamAttributes &attrs)
{
    ISegment *seg;
    if (!m_tags.contains(tagName)) {
        if (next())
            seg = next()->handle(tagName, attrs);
        else
            seg = UtilSegment::createPlainTextSegment(tagName.toString());
    } else {
        int start = UtilSegment::readAttr(attrs, "start", "1").toInt();
        int step = UtilSegment::readAttr(attrs, "step", "1").toInt();

        seg = new SeqSegment(start, step);
    }
    return seg;
}

void SeqTag::setNext(ITag *tag)
{
    m_nextTag = tag;
}

ITag *SeqTag::next() const
{
    return m_nextTag;
}


// ----------- SeqSegment ------------- //
SeqSegment::SeqSegment(int start, int step)
{
    m_current_count = m_start = start;
    m_step = step;
}

void SeqSegment::build(DataManager */*dm*/)
{
    m_current_count = m_start;
}

const QString SeqSegment::data()
{
    m_current_count += m_step;
    return QString::number(m_current_count);
}

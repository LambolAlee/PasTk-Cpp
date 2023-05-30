
#include "coretag.h"
#include "src/data/datamanager.h"


CoreTag::CoreTag()
{
    m_tags = {"data", "br", "tab"};
    m_nextTag = nullptr;
}

CoreTag::~CoreTag()
{
    delete m_nextTag;
    m_nextTag = nullptr;
}

QList<QString> CoreTag::tags() const
{
    return m_tags;
}

ISegment *CoreTag::handle(QStringView tagName, const QXmlStreamAttributes &attrs)
{
    ISegment *seg;
    if (!m_tags.contains(tagName)) {
        if (next())
            seg = next()->handle(tagName, attrs);
        else
            seg = UtilSegment::createPlainTextSegment(tagName.toString());
    } else if (tagName == QStringLiteral("data")) {
        seg = new DataSegment;
    } else {
        seg = new LineBreakSegment(tagName);
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


// ------------- LineBreakSegment -------------- //
LineBreakSegment::LineBreakSegment(QStringView type)
{
    m_break_type = type;
}

void LineBreakSegment::build(DataManager */*dm*/)
{
    m_data = (m_break_type == QStringLiteral("br")) ? "\n" : "\t";
}

const QString LineBreakSegment::data()
{
    return m_data;
}


// ------------- DataSegment -------------- //
DataSegment::~DataSegment()
{
    m_dm = nullptr;
}

void DataSegment::build(DataManager *dm)
{
    m_dm = dm;
}

const QString DataSegment::data()
{
    // TODO: DataManager object -> how to represent the current item
    return m_dm->castCurrent();
}

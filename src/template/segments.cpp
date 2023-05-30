
#include "segments.h"
#include <QList>

Segments::Segments()
{
    m_segments = new QList<ISegment *>;
    m_result = new QStringList;
}

Segments::~Segments()
{
    qDeleteAll(m_segments);
    qDeleteAll(m_result);
    m_segments = nullptr;
    m_result = nullptr;
}

void Segments::build(DataManager *dm)
{
    for (auto segment : *m_segments)
        segment->build(dm);
}

const QString Segments::data()
{
    m_result->clear();
    for (auto segment : *m_segments)
        m_result->append(segment->data());
    return m_result->join("");
}

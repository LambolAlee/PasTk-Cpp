
#include "segments.h"

Segments::Segments()
{
    m_segments = new QList<ISegment *>();
}

Segments::~Segments()
{
    qDeleteAll(m_segments);
    m_segments = nullptr;
}

void Segments::clear()
{
    m_segments->clear();
}

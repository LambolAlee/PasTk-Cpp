
#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <QList>
#include "segment.h"


class Segments
{
public:
    void clear();
    void addSegment(SegType type);

private:
    QList<Segment> m_segments;
};

#endif // SEGMENTS_H

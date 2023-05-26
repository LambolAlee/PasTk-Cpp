
#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <QList>
#include "ISegment.h"


class Segments
{
public:
    Segments();
    ~Segments();

    void clear();
    void addSegment(ISegment *segment);

private:
    QList<ISegment *> *m_segments;
};

#endif // SEGMENTS_H

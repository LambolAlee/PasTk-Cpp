
#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "ISegment.h"

class Segments
{
public:
    Segments();
    ~Segments();

    void build(DataManager *dm);
    const QString data();
    void append(ISegment *segment);

private:
    QList<ISegment *> *m_segments;
    QStringList *m_result;
};


#endif // SEGMENTS_H

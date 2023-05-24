
#include "segment.h"

Segment::Segment(SegType type, QObject *parent)
    : QObject{parent}
    , m_type(type)
{

}

const QString Segment::build(const DataManager &dm)
{

}


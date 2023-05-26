#ifndef ISEGMENT_H
#define ISEGMENT_H

#include <QString>

class DataManager;

class ISegment
{
public:
    virtual void build(DataManager *dm) =0;
    virtual const QString data() =0;
};

#endif // ISEGMENT_H

#ifndef ISEGMENT_H
#define ISEGMENT_H

class QString;
class DataManager;

class ISegment
{
public:
    virtual void build(const DataManager &dm) =0;
    virtual const QString data() =0;
};

#endif // ISEGMENT_H


#ifndef SEGMENT_H
#define SEGMENT_H


#include <QObject>
#include "src/utils/consts.h"

class DataManager;

class Segment : public QObject
{
    Q_OBJECT
public:
    explicit Segment(SegType type, QObject *parent = nullptr);
    const QString build(const DataManager &dm);

private:
    SegType m_type;

};

#endif // SEGMENT_H

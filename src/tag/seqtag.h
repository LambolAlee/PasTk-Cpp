
#ifndef SEQTAG_H
#define SEQTAG_H

#include "ITag.h"
#include "src/template/ISegment.h"


class SeqTag : public ITag
{
public:
    SeqTag();

public:
    QList<QString> tags() const override;
    ISegment *handle(QStringView tagName, [[maybe_unused]]const QXmlStreamAttributes &attrs) override;
    void setNext(ITag *tag) override;
    ITag *next() const override;
    void reset() const override;
};

#endif // SEQTAG_H

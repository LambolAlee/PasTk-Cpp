
#ifndef SEQTAG_H
#define SEQTAG_H

#include "ITag.h"
#include "src/template/utilsegment.h"


class SeqSegment : public ISegment
{
public:
    SeqSegment(int start, int step);

public:
    void build(DataManager *dm) override;
    const QString data() override;

private:
    int m_current_count;
    int m_start;
    int m_step;
};


class SeqTag : public ITag
{
public:
    SeqTag();
    ~SeqTag() override;

public:
    QList<QString> tags() const override;
    ISegment *handle(QStringView tagName, const QXmlStreamAttributes &attrs) override;
    void setNext(ITag *tag) override;
    ITag *next() const override;

private:
    ITag *m_nextTag = nullptr;
    QList<QString> m_tags;
};

#endif // SEQTAG_H


#ifndef CORETAG_H
#define CORETAG_H

#include "ITag.h"
#include "src/template/ISegment.h"


class CoreSegment : public ISegment
{
public:
    void build(const DataManager &dm) override;
    const QString data() override;
};


class CoreTag : public ITag
{
public:
    ~CoreTag() override;

public:
    QList<QString> tags() const override;
    ISegment *handle(QStringView tagName, [[maybe_unused]]const QXmlStreamAttributes &attrs) override;
    void setNext(ITag *tag) override;
    ITag *next() const override;
    void reset() const override;

private:
    ITag *m_nextTag;
};

#endif // CORETAG_H

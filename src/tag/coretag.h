
#ifndef CORETAG_H
#define CORETAG_H

#include "ITag.h"
#include "src/template/utilsegment.h"


// ------------- DataSegment -------------- //
class DataSegment : public ISegment
{
public:
    ~DataSegment();

    void build(DataManager *dm) override;
    const QString data() override;

private:
    DataManager *m_dm;
};

// ------------- LineBreakSegment -------------- //
class LineBreakSegment : public ISegment
{
public:
    LineBreakSegment(QStringView type);

    void build(DataManager *dm) override;
    const QString data() override;

private:
    QStringView m_break_type;
    QString m_data;
};


class CoreTag : public ITag
{
public:
    CoreTag();
    ~CoreTag();

public:
    QList<QString> tags() const override;
    ISegment *handle(QStringView tagName, const QXmlStreamAttributes &attrs) override;
    void setNext(ITag *tag) override;
    ITag *next() const override;

private:
    ITag *m_nextTag = nullptr;
    QList<QString> m_tags;
};

#endif // CORETAG_H

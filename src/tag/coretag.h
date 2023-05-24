
#ifndef CORETAG_H
#define CORETAG_H

#include "ITag.h"


class CoreTag : public ITag
{
public:
    ~CoreTag() override;

public:
    QList<QString> tags() const override;
    QVariant handle(QStringView tagName, const QXmlStreamAttributes &attrs) override;
    void setNext(ITag *tag) override;
    ITag *next() const override;
    void reset() const override;

private:
    ITag *m_nextTag;
};

#endif // CORETAG_H

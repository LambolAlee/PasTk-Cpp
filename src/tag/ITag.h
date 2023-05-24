
#ifndef ITAG_H
#define ITAG_H

#include <QList>

class QXmlStreamAttributes;

class ITag
{
public:
    virtual ~ITag() =0;
    virtual QList<QString> tags() const =0;
    virtual QVariant handle(QStringView tagName, const QXmlStreamAttributes &attrs) =0;
    virtual void setNext(ITag *tag) =0;
    virtual ITag *next() const =0;
    virtual void reset() const =0;
};

#endif // ITAG_H

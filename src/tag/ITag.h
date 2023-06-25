
#ifndef ITAG_H
#define ITAG_H

#include <QMap>

class QXmlStreamAttributes;
class ISegment;

class ITag
{
public:
    virtual ~ITag() =default;

    virtual QMap<QString, QString> tags() const =0;
    virtual ISegment *handle(QStringView tagName, const QXmlStreamAttributes &attrs) =0;
    virtual void setNext(ITag *tag) =0;
    virtual ITag *next() const =0;
};

#endif // ITAG_H

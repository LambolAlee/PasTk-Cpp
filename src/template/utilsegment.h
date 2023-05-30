
#ifndef UTILSEGMENT_H
#define UTILSEGMENT_H

#include "ISegment.h"

class QString;
class QXmlStreamAttributes;


// ------------- PlainTextSegment -------------- //
class PlainTextSegment : public ISegment
{
public:
    PlainTextSegment(const QString &text);

public:
    void build(DataManager *dm) override;
    const QString data() override;

private:
    QString m_text;
};


// ------------- UtilSegment namespace --------------- //
namespace UtilSegment
{
ISegment *createPlainTextSegment(const QString &text);
QString readAttr(const QXmlStreamAttributes &attrs, const QString &key, const QString &default_value);
}

#endif // UTILSEGMENT_H

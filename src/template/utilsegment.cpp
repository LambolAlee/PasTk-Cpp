
#include "utilsegment.h"
#include <QXmlStreamAttributes>

PlainTextSegment::PlainTextSegment(const QString &text)
{
    m_text = text;
}

void PlainTextSegment::build(DataManager */*dm*/) {}

const QString PlainTextSegment::data()
{
    return m_text;
}


ISegment *UtilSegment::createPlainTextSegment(const QString &text)
{
    return new PlainTextSegment(text);
}

QString UtilSegment::readAttr(const QXmlStreamAttributes &attrs, const QString &key, const QString &default_value)
{
    return (attrs.hasAttribute(key) ? attrs.value(key).toString() : default_value);
}

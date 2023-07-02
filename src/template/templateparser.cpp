
#include "templateparser.h"
#include "qdebug.h"
#include "segments.h"
#include "src/template/utilsegment.h"

TemplateParser::TemplateParser()
{
    m_chain = TagLoader::instance().chain();
}

TemplateParser::~TemplateParser()
{
    delete m_chain;
}

Segments *TemplateParser::parse(const QString &templateStr)
{
    auto tmp = QString("<xml>%1</xml>").arg(templateStr);
    m_xml.addData(tmp);

    Segments *segments = new Segments;
    while(!m_xml.atEnd()) {
        m_xml.readNext();
        if (m_xml.isStartElement()) {
            if (Q_UNLIKELY(m_xml.name() == QStringLiteral("xml"))) continue;
            segments->append(m_chain->handle(m_xml.name(), m_xml.attributes()));
        } else if (m_xml.isEndElement()) {
            continue;
        } else if (!m_xml.text().isEmpty()) {
            segments->append(
               UtilSegment::createPlainTextSegment(m_xml.text().toString())
            );
        }
    }

    if (m_xml.hasError()) {
        qDebug() << m_xml.errorString();
    }
    m_xml.clear();

    return segments;
}

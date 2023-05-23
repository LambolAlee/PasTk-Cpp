#include "tagloader.h"
#include <QDebug>

void TagLoader::parse(const QString &templateStr)
{
    auto tmp = QString("<xml>%1</xml>").arg(templateStr);
    m_xml.addData(tmp);
    while(!m_xml.atEnd()) {
        m_xml.readNext();
        if (m_xml.isStartElement()) {
            if (Q_UNLIKELY(m_xml.name() == QStringLiteral("xml"))) continue;

        } else if (m_xml.isEndElement()) {
            continue;
        } else if (!m_xml.text().isEmpty()) {

        }
    }
    if (m_xml.hasError()) {
        qDebug() << m_xml.errorString();
    }
    m_xml.clear();
}

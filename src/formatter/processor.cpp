#include "processor.h"


Processor::Processor(QList<QPluginLoader *> loaders)
{
    _stream.setString(&_data);
    for (auto &&loader: loaders) {
        IGenerator *generator = qobject_cast<IGenerator *>(loader->instance());
        _generators.append(generator);
    }
    auto lastItem = _generators.cend()-1;
    for (auto item = _generators.cbegin(); item < lastItem; ++item)
        (*item)->setNext(*(item +1));
}

void Processor::parse(const QString &templateStr)
{
    _res.clear();
    auto tmp = QString("<xml>%1</xml>").arg(templateStr);
    _xml.addData(tmp);
    while(!_xml.atEnd()) {
        _xml.readNext();
        if (_xml.isStartElement()) {
            if (Q_UNLIKELY(_xml.name() == QStringLiteral("xml"))) continue;
            if (auto *firstGen = begin(); firstGen)
                _res << firstGen->handle(_xml.name(), _xml.attributes());
        } else if (_xml.isEndElement()) {
            continue;
        } else if (!_xml.text().isEmpty()) {
            _res << _xml.text().toString();
        }
    }
    if (_xml.hasError()) {
        qDebug() << _xml.errorString();
    }
    _xml.clear();
}

QString Processor::yield(const QString &data)
{
    _data.clear();
    for (auto &&variant: _res) {
        if (variant.canConvert<std::function<QString()>>())
            _stream << variant.value<std::function<QString()>>()();
        else
            _stream << variant.toString();
    }
    return _stream.readAll().arg(data);
}

IGenerator *Processor::begin()
{
    for (auto &&generator: _generators) {
        if (generator->enabled())
            return generator;
    }
    return nullptr;
}

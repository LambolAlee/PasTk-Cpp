#include "seqgenerator.h"

#include "formatter/generatorhelper.cpp"


SeqGenerator::SeqGenerator() {
    _simpleMapping = {
        {"br", "\n"},
        {"tab", "\t"}
    };
}

SeqGenerator::~SeqGenerator()
{
    _nextGenerator = nullptr;
}

QStringList SeqGenerator::normalTags()
{
    return _simpleMapping.keys();
}

QStringList SeqGenerator::specialTags()
{
    return {"seq"};
}

QVariant SeqGenerator::handle(QStringView tagName, const QXmlStreamAttributes &attrs)
{
    if (_simpleMapping.contains(tagName.toString()))
        return _simpleMapping.value(tagName.toString());
    else if (tagName == GeneratorHelper::dataTag())
        return "%1";      // `data` is copied by the user previously, should be added into the string first of all
    else if (specialTags().contains(tagName))
        return QVariant::fromValue<std::function<QString()>>(addHandler(tagName, attrs));
    else {
        if (_nextGenerator)
            return _nextGenerator->handle(tagName, attrs);
        else
            return tagName.toString();
    }
}

void SeqGenerator::setNext(IGenerator *gen)
{
    _nextGenerator = gen;
}

IGenerator *SeqGenerator::next() const
{
    return _nextGenerator;
}

void SeqGenerator::finish()
{
    _firstRun = true;
    if (_nextGenerator)
        _nextGenerator->finish();
}

std::function<QString ()> SeqGenerator::addHandler(QStringView tagName, const QXmlStreamAttributes &attrs)
{
    auto readAttr = GeneratorHelper::readAttr;
    if (tagName == QLatin1String("seq")) {
        auto begin = readAttr(attrs, "begin", "0").toInt();
        auto suffix = readAttr(attrs, "suffix", ".");
        auto space = readAttr(attrs, "space", "yes");
        auto mode = readAttr(attrs, "mode", "en");

        auto handler = [this, begin, suffix, space, mode](){
            QStringList res;
            res << accumulate(begin, mode) << suffix;
            if (space == QStringLiteral("yes"))
                res << " ";
            return res.join("");
        };
        return handler;
    }
    return nullptr;
}

QString SeqGenerator::accumulate(int begin, const QString &/*mode*/)
{
    if (_firstRun) {
        _beginNum = begin;
        _firstRun = false;
    }
    // support Chinese mode later
    return QString::number(_beginNum++);
}

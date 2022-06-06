#include "seqgenerator.h"

#include "formatter/generatorhelper.cpp"

#include <QSettings>


SeqGenerator::SeqGenerator() {
    _simpleMapping = {
        {"br", "\n"},
        {"tab", "\t"}
    };
}

SeqGenerator::~SeqGenerator()
{
    _nextGenerator = nullptr;
    if (_settings) {
        delete _settings;
        _settings = nullptr;
    }
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
    if (!enabled())
        return deliverToNext(tagName, attrs);

    if (_simpleMapping.contains(tagName.toString()))
        return _simpleMapping.value(tagName.toString());
    else if (tagName == GeneratorHelper::dataTag())
        return "%1";      // `data` is copied by the user previously, should be added into the string first of all
    else if (specialTags().contains(tagName))
        return QVariant::fromValue<std::function<QString()>>(addHandler(tagName, attrs));
    else
        return deliverToNext(tagName, attrs);
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

QVariant SeqGenerator::deliverToNext(QStringView tagName, const QXmlStreamAttributes &attrs)
{
    if (_nextGenerator)
        return _nextGenerator->handle(tagName, attrs);
    else
        return tagName.toString();
}

bool SeqGenerator::enabled() const
{
    return _enabled;
}

void SeqGenerator::setEnabled(bool state)
{
    _enabled = state;
    _settings->setValue("enabled", state);
}

void SeqGenerator::setConfDir(QDir dir)
{
    auto confFile = dir.path() + QDir::separator() + QLatin1String("seqgenerator.ini");
    _settings = new QSettings(confFile, QSettings::IniFormat);

    if (!_settings->contains("enabled")) {
        _settings->setValue("enabled", true);
        _enabled = true;
    } else {
        _enabled = _settings->value("enabled").toBool();
    }
}

void SeqGenerator::sync()
{
    if (_settings)
        _settings->sync();
}

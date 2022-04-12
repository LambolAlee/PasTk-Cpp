#ifndef SEQGENERATOR_H
#define SEQGENERATOR_H

#include "formatter/generatorinterface.h"

#include <QObject>


class SeqGenerator : public QObject, public IGenerator
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "lambol.PasTk-Cpp.IGenerator" FILE "seqgenerator.json")
    Q_INTERFACES(IGenerator)

// IGenerator interface
public:
    SeqGenerator();
    ~SeqGenerator();

    QStringList normalTags() override;
    QStringList specialTags() override;
    QVariant handle(QStringView tagName, const QXmlStreamAttributes &attrs) override;

    void setNext(IGenerator *gen) override;
    IGenerator *next() const override;

    void finish() override;

protected:
    std::function<QString ()> addHandler(QStringView tagName, const QXmlStreamAttributes &attrs) override;

private:
    IGenerator *_nextGenerator = nullptr;
    QMap<QString, QString> _simpleMapping;

    bool _firstRun = true;
    int _beginNum = 0;

    QString accumulate(int begin, const QString &mode);
};

#endif // SEQGENERATOR_H

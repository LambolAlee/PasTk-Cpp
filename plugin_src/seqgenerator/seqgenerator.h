#ifndef SEQGENERATOR_H
#define SEQGENERATOR_H

#include "formatter/generatorinterface.h"

#include <QObject>


class QSettings;

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

    bool enabled() const override;
    void setEnabled(bool state) override;

    void setConfDir(QDir dir) override;
    void sync() override;

protected:
    std::function<QString ()> addHandler(QStringView tagName, const QXmlStreamAttributes &attrs) override;

private:
    IGenerator *_nextGenerator = nullptr;
    QMap<QString, QString> _simpleMapping;
    QSettings *_settings = nullptr;

    bool _enabled;
    bool _firstRun = true;
    int _beginNum = 0;

    QString accumulate(int begin, const QString &mode);
    QVariant deliverToNext(QStringView tagName, const QXmlStreamAttributes &attrs);
};

#endif // SEQGENERATOR_H

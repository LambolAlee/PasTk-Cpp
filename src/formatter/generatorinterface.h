#ifndef GENERATORINTERFACE_H
#define GENERATORINTERFACE_H

#include <QtPlugin>


class QXmlStreamAttributes;

class IGenerator
{
public:
    virtual ~IGenerator() = default;

    virtual QStringList normalTags() =0;
    virtual QStringList specialTags() =0;
    virtual QVariant handle(QStringView tagName, const QXmlStreamAttributes &attrs) =0;
    virtual void setNext(IGenerator *gen) =0;
    virtual IGenerator *next() const =0;
    virtual void finish() =0;

protected:
    virtual std::function<QString()> addHandler(QStringView tagName, const QXmlStreamAttributes &attrs) =0;
};

#define IGenrator_iid "lambol.PasTk-Cpp.IGenerator/1.0"
Q_DECLARE_INTERFACE(IGenerator, IGenrator_iid)

#endif // GENERATORINTERFACE_H

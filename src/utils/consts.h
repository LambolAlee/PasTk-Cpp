
#ifndef CONSTS_H
#define CONSTS_H

#include <QString>

namespace Consts
{

enum PasteType
{
    Continuous,
    Selection,
};

class DefaultTemplate {
public:
    static QString data;
    static QString name;
};

QString DefaultTemplate::data = QStringLiteral("<data/>");
QString DefaultTemplate::name = QStringLiteral("default");

}

#endif // CONSTS_H

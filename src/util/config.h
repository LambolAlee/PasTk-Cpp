#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>


class Config : public QSettings
{
    Q_OBJECT
public:
    Config();
};

#endif // CONFIG_H

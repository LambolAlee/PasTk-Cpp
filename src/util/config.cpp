#include "config.h"

#include <QApplication>

Config::Config()
    : QSettings(qApp->applicationDirPath().append("/config.ini"), QSettings::IniFormat)
{

}

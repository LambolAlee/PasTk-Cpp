#include "config.h"

#include <QApplication>
#include <QKeySequence>


Config::Config()
    : QSettings(qApp->applicationDirPath().append("/config.ini"), QSettings::IniFormat) {}

Config::~Config()
{
    saveTemplates();
}


// Template edit area --------------------->
const QStringList Config::getTemplatesNames() const
{
    return _templateHelper.getTemplatesNames();
}

const TemplateContent Config::getTemplate(const QString &name) const
{
    return _templateHelper.getTemplate(name);
}

void Config::setTemplate(const QString &name, const QString &templateString, const QString &description)
{
    _templateHelper.setTemplate(name, templateString, description);
}

void Config::loadTemplates()
{
    int size = beginReadArray("Templates");
    for (int i = 0; i < size; ++i) {
        setArrayIndex(i);
        _templateHelper.setTemplate(
                    value("name").toString(),
                    value("template").toString(),
                    value("description").toString());
    }
    endArray();
    _templateHelper.setModified(false);
}

void Config::saveTemplates()
{
    if (!_templateHelper.isModified()) return;

    qDebug() << "[Config] saving templates now..";

    beginGroup("Templates");
    remove("");
    endGroup();

    int i = 0;
    beginWriteArray("Templates");
    for (auto pair = _templateHelper.keyValueBegin(); pair != _templateHelper.keyValueEnd(); ++pair) {
        setArrayIndex(i++);
        setValue("name", pair->first);
        auto content = pair->second;
        setValue("template", content.first);
        setValue("description", content.second);
    }
    endArray();
    _templateHelper.setModified(false);
}

void Config::setDefaultTemplate(const QString &name)
{
    setKey(QStringLiteral("DefaultTemplate"), QStringLiteral("default_template"), name);
}

QPair<QString, TemplateContent> Config::getDefaultTemplate()
{
    auto name = getValue(QStringLiteral("DefaultTemplate"), QStringLiteral("default_template"), QString());
    if (name.isEmpty())
        return {};
    else
        return {name, getTemplate(name)};
}

bool Config::contains(const QString &name)
{
    return _templateHelper.contains(name);
}

void Config::remove(const QString &name)
{
    if (name == getDefaultTemplate().first)
        setDefaultTemplate(QString());
    _templateHelper.removeTemplate(name);
}

void Config::rename(const QString &oldName, const QString &newName)
{
    if (oldName == getDefaultTemplate().first)
        setDefaultTemplate(newName);
    _templateHelper.renameTemplate(oldName, newName);
}


// General Settings --------------------->
void Config::setLanguage(const QString &language)
{
    setKey(QStringLiteral("General"), QStringLiteral("language"), language);
}

QString Config::getLanguage()
{
    return getValue(QStringLiteral("General"), QStringLiteral("language"), defaults::getQString(defaults::language));
}

void Config::setMenuBarShow(bool show)
{
    setKey(QStringLiteral("General"), QStringLiteral("menubar_show"), show);
}

bool Config::getMenuBarShow()
{
    return getValue(QStringLiteral("General"), QStringLiteral("menubar_show"), defaults::menuBarShow);
}

void Config::setTopmost(bool onTop)
{
    setKey(QStringLiteral("General"), QStringLiteral("topmost"), onTop);
}

bool Config::getTopmost()
{
    return getValue(QStringLiteral("General"), QStringLiteral("topmost"), defaults::topmost);
}

void Config::setWindowVisible(bool visible)
{
    setKey(QStringLiteral("General"), QStringLiteral("window_visible"), visible);
}

bool Config::getWindowVisible()
{
    return getValue(QStringLiteral("General"), QStringLiteral("window_visible"), defaults::windowVisibility);
}

void Config::setClearAfterNewCopy(defaults::NewCopyOperation option)
{
    setKey(QStringLiteral("General"), QStringLiteral("new_copy_operation"), option);
}

defaults::NewCopyOperation Config::getClearAfterNewCopy()
{
    return getValue(QStringLiteral("General"), QStringLiteral("new_copy_operation"), defaults::NoClearOperation);
}


// Hotkey settings --------------------->
void Config::setCopyShortcut(const QKeySequence &sequence)
{
    setKey(QStringLiteral("Hotkey"), QStringLiteral("copy"), sequence);
}

QKeySequence Config::getCopyShortcut()
{
    return getValue(QStringLiteral("HotKey"), QStringLiteral("copy"), QKeySequence(defaults::getQString(defaults::copy)));
}

void Config::setRunPasteShortcut(const QKeySequence &sequence)
{
    setKey(QStringLiteral("Hotkey"), QStringLiteral("run_paste"), sequence);
}

QKeySequence Config::getRunPasteShortcut()
{
    return getValue(QStringLiteral("HotKey"), QStringLiteral("run_paste"), QKeySequence(defaults::getQString(defaults::runPaste)));
}

void Config::setPasteShortcut(const QKeySequence &sequence)
{
    setKey(QStringLiteral("Hotkey"), QStringLiteral("paste"), sequence);
}

QKeySequence Config::getPasteShortcut()
{
    return getValue(QStringLiteral("HotKey"), QStringLiteral("paste"), QKeySequence(defaults::getQString(defaults::paste)));
}

void Config::setSkipPasteShortcut(const QKeySequence &sequence)
{
    setKey(QStringLiteral("Hotkey"), QStringLiteral("skip"), sequence);
}

QKeySequence Config::getSkipShortcut()
{
    return getValue(QStringLiteral("HotKey"), QStringLiteral("skip"), QKeySequence(defaults::getQString(defaults::skip)));
}


// Program settings --------------------->
void Config::setLastUsedMode(int mode)
{
    setKey(QStringLiteral("Program"), QStringLiteral("last_used_mode"), mode);
}

int Config::getLastUsedMode()
{
    return getValue(QStringLiteral("Program"), QStringLiteral("last_used_mode"), defaults::mode);
}


// helper function --------------------->
template<typename T>
void Config::setKey(const QString &group, const QString &key, T value)
{
    beginGroup(group);
    setValue(key, value);
    endGroup();
}

template<typename T>
T Config::getValue(const QString &group, const QString &key, T default_)
{
    beginGroup(group);
    QVariant t = value(key, default_);
    endGroup();
    return t.value<T>();
}

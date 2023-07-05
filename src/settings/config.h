#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

#include "defaultsettings.h"
#include "src/template/templatehelper.h"


class Config : private QSettings
{
    Q_OBJECT

public:
    Config();
    ~Config();

    using QSettings::sync;

public:
// Template edit area --------------------->
    const QStringList getTemplateNameList() const;
    const QString getTemplateStringByName(const QString &name) const;
    const TemplatePair getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString);
    void setTemplate(const TemplatePair &pair);

    void loadTemplates();
    void saveTemplates();

    void setDefaultTemplate(const QString &name);
    void setDefaultTemplate();
    TemplatePair getDefaultTemplate();
    int templateCount();
    bool contains(const QString &name);
    bool remove(const QString &name);
    void rename(const QString &oldName, const QString &newName);

// General settings --------------------->
    void setLanguage(const QString &language);
    QString getLanguage();

    void setMenuBarShow(bool show);
    bool getMenuBarShow();

    void setTopmost(bool onTop);
    bool getTopmost();

    void setWindowVisible(bool visible);
    bool getWindowVisible();

    void setClearAfterNewCopy(defaults::NewCopyOperation option);
    defaults::NewCopyOperation getClearAfterNewCopy();

// Hotkey settings --------------------->
    void setCopyShortcut(const QKeySequence &sequence);
    QKeySequence getCopyShortcut();

    void setRunPasteShortcut(const QKeySequence &sequence);
    QKeySequence getRunPasteShortcut();

    void setPasteShortcut(const QKeySequence &sequence);
    QKeySequence getPasteShortcut();

    void setSkipPasteShortcut(const QKeySequence &sequence);
    QKeySequence getSkipShortcut();

// Program settings --------------------->
    void setLastUsedMode(int mode);
    int getLastUsedMode();

private:
    TemplateHelper &m_template_helper = TemplateHelper::instance();

// helper function --------------------->
    template<typename T> void setKey(const QString &group, const QString &key, T value);
    template<typename T> T getValue(const QString &group, const QString &key, T default_);
    bool repairEmptyTemplate();
};

#endif // CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

#include "defaultsettings.h"
#include "formatter/templatehelper.h"


class Config : private QSettings
{
    Q_OBJECT

public:
    Config();
    ~Config();

public:
// Template edit area --------------------->
    const QStringList getTemplatesNames() const;
    const QString getTemplate(const QString &name) const;
    void setTemplate(const QString &name, const QString &templateString);

    void loadTemplates();
    void saveTemplates();

// General settings --------------------->
    void setLanguage(const QString &language);
    QString getLanguage();

    void setMenuBarShow(bool show);
    bool getMenuBarShow();

    void setTopmost(bool onTop);
    bool getTopmost();

    void setWindowVisibility(bool visible);
    bool getWindowVisibility();

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
    TemplateHelper _templateHelper;

// helper function --------------------->
    template<typename T> void setKey(const QString &group, const QString &key, T value);
    template<typename T> T getValue(const QString &group, const QString &key, T default_);
};

#endif // CONFIG_H

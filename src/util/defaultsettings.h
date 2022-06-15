#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QString>


namespace defaults
{
    enum NewCopyOperation { ClearHistory, NoClearOperation };
    // General settings
    const std::string_view language = "en_US";
    constexpr bool menuBarShow = false;
    constexpr bool topmost = false;
    constexpr bool windowVisibility = false;
    constexpr int clearAfterNewCopy = NoClearOperation;

    // Hotkey settings
    constexpr std::string_view copy = "Ctrl+Shift+C";
    constexpr std::string_view runPaste = "Ctrl+Shift+V";
    constexpr std::string_view paste = "Ctrl+Shift+.";
    constexpr std::string_view skip = "Ctrl+Shift+/";

    // Program settings
    constexpr int mode = 0;

    const QString getQString(std::string_view str);
}

#endif // DEFAULTSETTINGS_H

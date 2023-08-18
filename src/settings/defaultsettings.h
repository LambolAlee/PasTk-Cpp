#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QString>


namespace defaults
{
    enum NewCopyOperation { ClearHistory, ReserveHistory };
    // General settings
    const std::string_view language = "en_US";
    constexpr bool topmost = false;
    constexpr bool windowVisibility = false;
    constexpr int clearAfterNewCopy = ReserveHistory;

    // Hotkey settings
    constexpr std::string_view copy = "Ctrl+Alt+C";
    constexpr std::string_view runPaste = "Ctrl+Alt+V";
    constexpr std::string_view paste = "Ctrl+Alt+.";
    constexpr std::string_view skip = "Ctrl+Alt+/";

    // Program settings
    constexpr int mode = 0;

    const QString getQString(std::string_view str);
}

#endif // DEFAULTSETTINGS_H

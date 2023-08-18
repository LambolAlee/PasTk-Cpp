#include "pasteutil.h"
#include <QWidget>
#include <QTimer>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

#include <AppKit/AppKit.h>
#include <Carbon/Carbon.h>

PasteUtil::PasteUtil()
{
    // info.plist: set the LSUIElement to YES
    // and then open the sentence below to prevent the app to occupy other apps' focus
//    [NSApp setActivationPolicy: NSApplicationActivationPolicyAccessory];
    check_accessibility_trusted();
}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste()
{
    [NSApp hide: NSApp];
    QTimer::singleShot(200, this, &PasteUtil::execute_paste);
}

void PasteUtil::paste(QWidget */*window*/)
{
    paste();
}

void PasteUtil::execute_paste()
{
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventSourceSetLocalEventsFilterDuringSuppressionState(source, kCGEventFilterMaskPermitLocalMouseEvents | kCGEventFilterMaskPermitSystemDefinedEvents, kCGEventSuppressionStateSuppressionInterval);

    CGEventRef v_p = CGEventCreateKeyboardEvent(source, (CGKeyCode)kVK_ANSI_V, YES);
    CGEventSetFlags(v_p, kCGEventFlagMaskCommand);
    CGEventRef v_r = CGEventCreateKeyboardEvent(source, (CGKeyCode)kVK_ANSI_V, NO);
    CGEventSetFlags(v_r, kCGEventFlagMaskCommand);

    CGEventPost(kCGAnnotatedSessionEventTap, v_p);
    CGEventPost(kCGAnnotatedSessionEventTap, v_r);

    CFRelease(v_p);
    CFRelease(v_r);
    CFRelease(source);

    [NSApp activateIgnoringOtherApps:YES];
}

bool PasteUtil::check_accessibility_trusted()
{
    NSDictionary *options = @{(id)kAXTrustedCheckOptionPrompt : @YES};
    BOOL accessibilityEnabled = AXIsProcessTrustedWithOptions((CFDictionaryRef)options);
    if (!accessibilityEnabled) {
        QDesktopServices::openUrl(QUrl(QDir::currentPath()));
    }
    return accessibilityEnabled;
}

bool PasteUtil::copy(const QString &text)
{
    // TODO: maybe catch some error
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard writeObjects:@[text.toNSString()]];
    return true;
}

void PasteUtil::test()
{
    // switch the system theme to light
    NSApp.appearance = [NSAppearance appearanceNamed:NSAppearanceNameAqua];
}

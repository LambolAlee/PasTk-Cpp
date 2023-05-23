#include "pasteutil.h"

#include <QClipboard>
#include <QTimer>

#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>


PasteUtil::PasteUtil() {}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste(const QString &str)
{
    _clipBoard->setText(str);
    paste();
}

void PasteUtil::paste(bool directly)
{
    if (!directly) {
        static NSApplication *id_of_me = [NSApp self];
        [NSApp hide: id_of_me];
    }
    QTimer::singleShot(100, this, &PasteUtil::_paste);
}

void PasteUtil::_paste() const
{
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventSourceSetLocalEventsFilterDuringSuppressionState(source, kCGEventFilterMaskPermitLocalMouseEvents | kCGEventFilterMaskPermitSystemDefinedEvents, kCGEventSuppressionStateSuppressionInterval);

    CGEventRef v_press = CGEventCreateKeyboardEvent(source, (CGKeyCode)kVK_ANSI_V, YES);
    CGEventSetFlags(v_press, kCGEventFlagMaskCommand);
    CGEventRef v_release = CGEventCreateKeyboardEvent(source, (CGKeyCode)kVK_ANSI_V, NO);
    CGEventSetFlags(v_release, kCGEventFlagMaskCommand);

    CGEventPost(kCGAnnotatedSessionEventTap, v_press);
    CGEventPost(kCGAnnotatedSessionEventTap, v_release);

    CFRelease(v_press);
    CFRelease(v_release);
    CFRelease(source);

    [NSApp activateIgnoringOtherApps:YES];
}

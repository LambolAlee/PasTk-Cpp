#include "pasteutil.h"
#include <QWidget>
#include <QTimer>

#include <AppKit/AppKit.h>
#include <Carbon/Carbon.h>


PasteUtil::PasteUtil()
{
    // info.plist: set the LSUIElement to YES
    // and then open the sentence below to prevent the app to occupy other apps' focus
//    [NSApp setActivationPolicy: NSApplicationActivationPolicyAccessory];
}
PasteUtil::~PasteUtil() {}

void PasteUtil::paste([[maybe_unused]] QWidget *window)
{
    [NSApp hide: NSApp];
    QTimer::singleShot(200, this, &PasteUtil::execute_paste);
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

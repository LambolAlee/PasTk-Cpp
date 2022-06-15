QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

TARGET     = PasTk-Cpp

win32 {
    LIBS += -lDwmapi -luser32

    SOURCES += \
        ui/framelesswindow.cpp \
        util/pasteutil.cpp

    HEADERS += ui/framelesswindow.h

    RC_ICONS = resources/logo/PasTk_logo.ico
}

macx {
    LIBS += \
        -framework AppKit \
        -framework Carbon
    QMAKE_INFO_PLIST = ./Info.plist

    OBJECTIVE_SOURCES += util/pasteutil.mm

    ICON = resources/logo/PasTk_logo.icns
}

include(third-party/singleapplication/singleapplication.pri)
include(third-party/qhotkey/qhotkey.pri)
DEFINES += QAPPLICATION_CLASS=QApplication

SOURCES += \
    datamanager/datamanager.cpp \
    datamanager/itemdelegate.cpp \
    formatter/generatorhelper.cpp \
    formatter/pluginmanager.cpp \
    formatter/processor.cpp \
    formatter/templatehelper.cpp \
    main.cpp \
    ui/aboutpastkcpp.cpp \
    ui/bottombar.cpp \
    ui/continuouspastewindow.cpp \
    ui/detailview.cpp \
    ui/home.cpp \
    ui/itemeditordialog.cpp \
    ui/mergewindow.cpp \
    ui/pastemanager.cpp \
    ui/preferences.cpp \
    ui/selectionpastewindow.cpp \
    ui/suspendscrollbar.cpp \
    ui/systray.cpp \
    ui/templateeditor.cpp \
    ui/templatepanel.cpp \
    ui/titlebar.cpp \
    util/clipboardlistner.cpp \
    util/config.cpp \
    util/defaultsettings.cpp \
    util/postoffice.cpp \
    util/util.cpp

HEADERS += \
    datamanager/datamanager.h \
    datamanager/itemdelegate.h \
    formatter/generatorhelper.h \
    formatter/generatorinterface.h \
    formatter/pluginmanager.h \
    formatter/processor.h \
    formatter/templatehelper.h \
    ui/aboutpastkcpp.h \
    ui/bottombar.h \
    ui/continuouspastewindow.h \
    ui/detailview.h \
    ui/home.h \
    ui/itemeditordialog.h \
    ui/mergewindow.h \
    ui/pastemanager.h \
    ui/preferences.h \
    ui/selectionpastewindow.h \
    ui/suspendscrollbar.h \
    ui/systray.h \
    ui/templateeditor.h \
    ui/templatepanel.h \
    ui/titlebar.h \
    util/clipboardlistner.h \
    util/config.h \
    util/defaultsettings.h \
    util/pasteutil.h \
    util/Singleton.h \
    util/postoffice.h \
    util/util.h \
    version.h

FORMS += \
    ui/aboutpastkcpp.ui \
    ui/bottombar.ui \
    ui/continuouspastewindow.ui \
    ui/home.ui \
    ui/itemeditordialog.ui \
    ui/mergewindow.ui \
    ui/preferences.ui \
    ui/selectionpastewindow.ui \
    ui/templateeditor.ui \
    ui/templatepanel.ui \
    ui/titlebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/rc.qrc

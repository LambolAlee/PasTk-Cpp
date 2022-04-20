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
    main.cpp \
    ui/bottombar.cpp \
    ui/detaillistview.cpp \
    ui/home.cpp \
    ui/itemfloatbuttons.cpp \
    ui/templateeditor.cpp \
    ui/titlebar.cpp \
    util/cframelessbridge.cpp \
    util/config.cpp

HEADERS += \
    datamanager/datamanager.h \
    datamanager/itemdelegate.h \
    formatter/generatorhelper.h \
    formatter/generatorinterface.h \
    ui/bottombar.h \
    ui/detaillistview.h \
    ui/home.h \
    ui/itemfloatbuttons.h \
    ui/templateeditor.h \
    ui/titlebar.h \
    util/cframelessbridge.h \
    util/config.h \
    util/pasteutil.h \
    util/Singleton.h

FORMS += \
    ui/bottombar.ui \
    ui/home.ui \
    ui/itemfloatbuttons.ui \
    ui/templateeditor.ui \
    ui/titlebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/rc.qrc

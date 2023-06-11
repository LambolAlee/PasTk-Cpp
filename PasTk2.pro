QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    OBJECTIVE_SOURCES += \
        src/paste/pasteutil.mm \
        src/data/clipboardlistener_mac.cpp

    LIBS += -framework Cocoa
    LIBS += -framework Carbon

    QMAKE_INFO_PLIST = ./Info.plist
    ICON = qrc/logo/PasTk_logo.icns
}

win32 {
    SOURCES += \
        src/paste/pasteutil.cpp \
        src/data/clipboardlistener.cpp

    RC_ICONS = qrc\logo\PasTk_logo.ico
}

SOURCES += \
    src/ui/detailview.cpp \
    src/data/datamanager.cpp \
    src/main.cpp \
    src/settings/config.cpp \
    src/settings/defaultsettings.cpp \
    src/tag/coretag.cpp \
    src/tag/seqtag.cpp \
    src/tag/tagloader.cpp \
    src/template/segments.cpp \
    src/template/templatehelper.cpp \
    src/template/templateparser.cpp \
    src/template/utilsegment.cpp \
    src/ui/aboutpastkcpp.cpp \
    src/ui/bottombar.cpp \
    src/ui/itemeditordialog.cpp \
    src/ui/pastkwindow.cpp \
    src/ui/preferences.cpp \
    src/ui/suspendscrollbar.cpp \
    src/ui/systray.cpp \
    src/ui/templateeditorwindow.cpp \
    src/utils/util.cpp \
    src/utils/windowhelper.cpp

HEADERS += \
    src/ui/detailview.h \
    src/data/clipboardlistener.h \
    src/data/datacaster.h \
    src/data/datamanager.h \
    src/settings/config.h \
    src/settings/defaultsettings.h \
    src/tag/ITag.h \
    src/tag/coretag.h \
    src/tag/seqtag.h \
    src/tag/tagloader.h \
    src/template/ISegment.h \
    src/template/segments.h \
    src/template/templatehelper.h \
    src/template/templateparser.h \
    src/template/utilsegment.h \
    src/ui/aboutpastkcpp.h \
    src/ui/bottombar.h \
    src/ui/itemeditordialog.h \
    src/ui/pastkwindow.h \
    src/ui/preferences.h \
    src/ui/suspendscrollbar.h \
    src/ui/systray.h \
    src/ui/templateeditorwindow.h \
    src/utils/Singleton.h \
    src/paste/pasteutil.h \
    src/utils/consts.h \
    src/utils/util.h \
    src/utils/windowhelper.h \
    src/version.h

FORMS += \
    src/ui/aboutpastkcpp.ui \
    src/ui/bottombar.ui \
    src/ui/itemeditordialog.ui \
    src/ui/pastkwindow.ui \
    src/ui/preferences.ui \
    src/ui/templateeditorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc/icons/icons.qrc \
    qrc/logo/logo.qrc \
    qrc/style/styles.qrc

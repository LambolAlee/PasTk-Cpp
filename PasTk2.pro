QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    OBJECTIVE_SOURCES += src/paste/pasteutil.mm
    LIBS += -framework Cocoa
    LIBS += -framework Carbon

    QMAKE_INFO_PLIST = ./Info.plist
}

win32 {
    SOURCES += src/paste/pasteutil.cpp
}

SOURCES += \
    src/data/datacaster.cpp \
    src/data/datamanager.cpp \
    src/main.cpp \
    src/settings/config.cpp \
    src/settings/defaultsettings.cpp \
    src/tag/coretag.cpp \
    src/tag/seqtag.cpp \
    src/tag/tagloader.cpp \
    src/template/segment.cpp \
    src/template/segments.cpp \
    src/template/templateparser.cpp \
    src/ui/bottombar.cpp \
    src/ui/pastkwindow.cpp \
    src/ui/templateeditorwindow.cpp \

HEADERS += \
    src/data/datacaster.h \
    src/data/datamanager.h \
    src/settings/config.h \
    src/settings/defaultsettings.h \
    src/tag/ITag.h \
    src/tag/coretag.h \
    src/tag/seqtag.h \
    src/tag/tagloader.h \
    src/template/segment.h \
    src/template/segments.h \
    src/template/templateparser.h \
    src/ui/bottombar.h \
    src/ui/pastkwindow.h \
    src/ui/templateeditorwindow.h \
    src/utils/Singleton.h \
    src/paste/pasteutil.h \
    src/utils/consts.h

FORMS += \
    src/ui/bottombar.ui \
    src/ui/pastkwindow.ui \
    src/ui/templateeditorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

win32 {
    LIBS += -lDwmapi -luser32

    SOURCES += \
        src/ui/framelesswindow.cpp \
        src/util/pasteutil.cpp

    HEADERS += src/ui/framelesswindow.h

    RC_ICONS = src/resources/logo/PasTk_logo.ico
}

macx {
    LIBS += \
        -framework AppKit \
        -framework Carbon

    OBJECTIVE_SOURCES += src/util/pasteutil.mm

    ICON = src/resources/logo/PasTk_logo.icns
}

include(src/third-party/singleapplication/singleapplication.pri)
include(src/third-party/qhotkey/qhotkey.pri)
DEFINES += QAPPLICATION_CLASS=QApplication

SOURCES += \
    src/main.cpp \
    src/ui/bottombar.cpp \
    src/ui/detaileditor.cpp \
    src/ui/home.cpp \
    src/ui/templateeditor.cpp \
    src/ui/titlebar.cpp \
    src/util/cframelessbridge.cpp

HEADERS += \
    src/ui/bottombar.h \
    src/ui/detaileditor.h \
    src/ui/home.h \
    src/ui/templateeditor.h \
    src/ui/titlebar.h \
    src/util/cframelessbridge.h \
    src/util/pasteutil.h \
    src/util/Singleton.h

FORMS += \
    src/ui/bottombar.ui \
    src/ui/detaileditor.ui \
    src/ui/home.ui \
    src/ui/templateeditor.ui \
    src/ui/titlebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources/rc.qrc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    OBJECTIVE_SOURCES += src/utils/paste/pasteutil.mm
    LIBS += -framework Cocoa
    LIBS += -framework Carbon

    QMAKE_INFO_PLIST = ./Info.plist
}

win32 {
    SOURCES += src/utils/paste/pasteutil.cpp
}

SOURCES += \
    src/main.cpp \
    src/template/tagloader.cpp \
    src/ui/bottombar.cpp \
    src/ui/pastkwindow.cpp \
    src/ui/templateeditorwindow.cpp \

HEADERS += \
    src/template/tagloader.h \
    src/ui/bottombar.h \
    src/ui/pastkwindow.h \
    src/ui/templateeditorwindow.h \
    src/utils/Singleton.h \
    src/utils/paste/pasteutil.h

FORMS += \
    src/ui/bottombar.ui \
    src/ui/pastkwindow.ui \
    src/ui/templateeditorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

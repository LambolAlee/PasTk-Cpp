TEMPLATE = lib
CONFIG += plugin

CONFIG += c++20

QT += core
TARGET = $$qtLibraryTarget(seqgenerator)
DESTDIR = ../../plugins
INCLUDEPATH += ../../src

DISTFILES += seqgenerator.json

HEADERS += \
    seqgenerator.h

SOURCES += \
    seqgenerator.cpp

!isEmpty(target.path): INSTALLS += target

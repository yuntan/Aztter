TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR +=  ../lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

TARGET = aztter

HEADERS += \
    aztteroauth.h \
    aztterplugin.h

SOURCES += \
    aztteroauth.cpp \
    aztterplugin.cpp
